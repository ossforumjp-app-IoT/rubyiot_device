# mruby script

# initial threshold of temperature
TEMPTHR_HI = 30.0
TEMPTHR_LO = 5.0

# Xbee address and setting
FRAME_ID = 0x01
# for FAE Co.
#ADD64_HI = 0x0013A200
#ADD64_LO = 0x405E08F7
# for test
ADD64_HI = 0x0013A200
ADD64_LO = 0x406F44F0
ADD16_HI = 0x00
ADD16_LO = 0x00
BROADC_RAD = 0x00
OPT = 0x00

class Fan
  def initialize
    @port_onoff = 0x10
    @port_status = 0x11
    @status = 1
    @gpio = GPIO.new
    @gpio.mode(@port_onoff, GPIO::OUTPUT)
    @gpio.mode(@port_status, GPIO::INPUT)
    @gpio.write(@port_onoff, GPIO::HIGH)
  end

  def on
    @gpio.write(@port_onoff, GPIO::LOW)
  end

  def off
    @gpio.write(@port_onoff, GPIO::HIGH)
  end

  def get_status
    d = @gpio.read(@port_status)
    if d == 0
      @status = 1
    else
      @status = 0
    end
    return @status
  end

  def get_onoff
    if @status == 0
      return "-"
    else
      onoff = @gpio.read(@port_onoff)
      if onoff == 0
        return "1"
      else
        return "0"
      end
    end
  end
end

class Sensor < I2CMaster
  def initialize
    @sensor_add = 0x48
    @status = 1
    super(Sensor::MFS2, Sensor::PIN_LOC2, 100000)
  end

  def read(command)
    super(@sensor_add, command)
  end

  def get_status
    d = self.read(0x03)
    if d < 0
      @status = 0
    else
      sta = (d & 0x60) >> 5
      if sta > 2
        @status = 0
      else
        @status = 1
      end
    end
    return @status
  end

  def get_temperature
    if @status == 0
      return "+---.-"
    else
      val_h = self.read(0x00)
      val_l = self.read(0x01)
      val = val_h << 8
      val |= val_l
      val = val >> 3
      if (val & 0x1000) > 0
        pm = "-"
        a = (val - 8192) / 16
      else
        pm = "+"
        a = val / 16
      end
      if a > -0.05 && a < 0.05
        pm = "+"
      end
      return pm + "%05.1f" % a.abs
    end
  end
end

class Xbee < UART
  def initialize
    super(Xbee::MFS3, Xbee::PIN_LOC2, 115200)
  end

  def read
    d = super()
    if d == 0x7D
      d = super()
      d ^= 0x20
    end
    return d
  end

  def get_message
    # get start delimiter
    loop do
      d = self.read
      if d == 0x7E
        break
      end
    end
    # get message length
    len = 0
    for i in 0..1
      d = self.read
      len |= d << (8 - i * 8)
    end
    # frame type
    type = self.read
    if type == 0x90
      # get Frame90 message
      arr = []
      # get 64bits address, 16bits address and options
      (8 + 2 + 1).times do
        d = self.read
        arr << d
      end
      # get RF data
      pldsize = len - 12
      d = self.read
      arr << d
      pld = d.chr
      (pldsize - 1).times do
        d = self.read
        arr << d
        pld += d.chr
      end
      # get checksum
      chs = self.read
      bysum = 0x90 + arr.inject{|sum, n| sum + n}
      if chs == (0xFF - (bysum & 0xFF))
        return type, pld
      else
        return type, "false"
      end
    else
      return type, "don't care"
    end
  end

  def send_frame10_message(mes)
    len = 0x0E + mes.bytesize
    # start delimiter, message length
    arr1 = [0x7E]
    for i in 0..1
      d = (len >> (8 - i * 8)) & 0xFF
      arr1 << d
    end
    # API frame type, frame ID
    arr2 = [0x10, FRAME_ID]
    # 64bits address High
    for i in 0..3
      d = ADD64_HI >> (24 - i * 8) & 0xFF
      arr2 << d
    end
    # 64bits address Low
    for i in 0..3
      d = ADD64_LO >> (24 - i * 8) & 0xFF
      arr2 << d
    end
    # 16bits address, broadcast radius, options
    arr2 << ADD16_HI << ADD16_LO << BROADC_RAD << OPT
    bysum = arr2.inject{|sum, n| sum + n}
    # data
    arr2 << mes
    bysum += mes.bytes.inject{|sum, n| sum + n}
    # checksum
    d = 0xFF - (bysum & 0xFF)
    arr2 << d
    arr = arr1 + arr2
    self.write(arr)
  end

  def self.open
    Xbee.new
  end
end

class App
  def initialize
    # initialize setting, parameters etc...
    @threshold_hi = TEMPTHR_HI
    @threshold_lo = TEMPTHR_LO
    @fan = Fan.new
    @sensor = Sensor.new
    @xbee = Xbee.open
    GC.start
  end

  def main
    # main process
    fan_status = @fan.get_status
    sensor_status = @sensor.get_status
    device_status = ((fan_status << 1) | sensor_status).to_s
    fan_onoff = @fan.get_onoff
    temperature = @sensor.get_temperature
    if sensor_status == 0
      condition = "-"
    else
      if temperature.to_f > @threshold_hi
        condition = "1"
      elsif  temperature.to_f < @threshold_lo
        condition = "2"
      else
        condition = "0"
      end
    end
    payload = device_status + "," + fan_onoff + "," + temperature + "," + condition
    @xbee.send_frame10_message(payload)
    GC.start
  end

  def get_message
    # receive message etc...
    if @xbee.received?
      frame_type, message = @xbee.get_message
      if frame_type == 0x90
        if message != "false"
          received_data = message.split(",")
          for i in 0..3
            if i == 0 || i == 1
              received_data[i] = received_data[i].to_i
            else
              received_data[i] = received_data[i].to_f
            end
          end
          case received_data[1]
          when 1
            @fan.on
          when 0
            @fan.off
          end
          @threshold_hi = received_data[2]
          @threshold_lo = received_data[3]
        end
      end
      @xbee.flush
    end
    GC.start
  end
end
