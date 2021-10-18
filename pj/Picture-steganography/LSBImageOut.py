from PIL import Image
import struct


#  来自PIL import image
#  image = Image.open（"test.png"）
#  image_out = Image.new（image.mode，image.size）

#  pixels = list（image.getdata（））
#  image_out.putdata（pixels）
#  image_out.save（'test_out.png'）
# 这里没有编写头文件！！

def get_stream():
    # 获取要隐藏的文件内容
    File = "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\Figure1-origin.png"

    f = open(File, "rb")  # 要读取二进制文件，比如图片、视频等等，用'rb'模式打开文件
    s = f.read()
    stream = ""
    for i in range(len(s)):
        # 逐个字节将要隐藏的文件内容转换为二进制，并拼接起来
        # 1.使用bin()函数将十进制的数转换为二进制
        # 2.由于bin()函数转换二进制后，二进制字符串的前面会有"0b"来表示这个字符串是二进制形式，所以用replace()替换为空
        # 3.又由于这样替换之后是七位，而正常情况下每个字符由8位二进制组成，将其填充为8位
        stream = stream + (bin(s[i]).replace('0b', '')).zfill(8)  # s[i]为该位置字符的十进制表示的ascll码

    f.closed

    return stream

def out_file(stream):
    f = open("find.png", "wb")  # 要读取二进制文件，比如图片、视频等等，用'rb'模式打开文件
    for x in stream:
        a = struct.pack('B', x)
        f.write(a)
    f.close()





im=Image.open(
    "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\out.png")

width=im.size[0]
height=im.size[1]

print("width:" + str(width))
print("height:" + str(height))

lenth = 976336

cnt = 0
stream = ""
bytes = []


for h in range(0, height):
    for w in range(0, width):
        # 获得(w,h)点像素的值

        pixel=im.getpixel((w, h))
        R = pixel[0]  # R
        G = pixel[1]  # G
        B = pixel[2]  # B
        # 此处，依次从R、G、B修改个颜色通道获得最低位的隐藏信息
        if cnt < lenth:
            stream += str(R%2)  # R
            cnt += 1
        if cnt < lenth:
            stream += str(G%2)  # G
            cnt+=1
        if cnt < lenth:
            stream += str(B%2)  # B
            cnt += 1

        if cnt == lenth:
            break
    if cnt == lenth:
            break


for i in range(0, len(stream), 8):
    # 以每8位为一组二进制，转换为十进制
    bytes.append(int(stream[i:i + 8], 2))

out_file(bytes)





