import smbus
import time
import socket

i2c = smbus.SMBus(3) # 在Linux上，通常是1（I2C-1）
addr = 0x44 # 定义I2C地址和寄存器
i2c.write_byte_data(addr,0x23,0x34) # 寄存器地址
time.sleep(0.5)

def STH30():
    global i2c,addr
    i2c.write_byte_data(addr,0xe0,0x0)
    data = i2c.read_i2c_block_data(addr,0x0,6)
    rawT = ((data[0]) << 8) | (data[1])
    rawR = ((data[3]) << 8) | (data[4])

    timestamp = time.time()
    formatted_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(timestamp))

    temp = -45 + rawT * 175 / 65535
    print (formatted_time + " 当前温度 temperature: " + str(round(temp,2)) + " ℃")
    RH = 100 * rawR / 65535
    print (formatted_time + " 当前湿度    humidity: " + str(round(RH,2)) + " %RH")
    
    
    str1 = str(round(temp,2)) + ";" + str(round(RH,2));
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # 2.准备接收方的地址
    # 192.168.65.149 表示目的地ip
    # 30000  表示目的地端口
    udp_socket.sendto(str1.encode("utf-8"), ("127.0.0.1", 23336))
    # udp_socket.sendto(str1.encode("utf-8"), ("192.168.1.233", 23336))

    # 3.关闭套接字
    #udp_socket.close()
    
    
    time.sleep(3)

if __name__ == "__main__":
    try:
        while True:
            STH30()
            time.sleep(5)
    except IOError as e:
        print(e)

