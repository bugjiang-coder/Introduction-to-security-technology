from PIL import Image


# 要被隐写的介质文件 -校门图片-
fileMedium = "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\Figure3-origin.png"
# 要隐写的图片 -我的证件照-
fileHide = "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\证件照.png"

#  为了保证数据确定数据的大小，所以每次隐写文件，总要用前32位来记录文件的大小

# 获取要隐藏的文件内容


def get_bytes(fileHide):
    f = open(fileHide, "rb")  # 要读取二进制文件，比如图片、视频等等，用'rb'模式打开文件
    s = f.read()
    bytes = ""
    for i in range(len(s)):
        # 逐个字节将要隐藏的文件内容转换为二进制，并拼接起来
        # 1.使用bin()函数将十进制的数转换为二进制
        # 2.由于bin()函数转换二进制后，二进制字符串的前面会有"0b"来表示这个字符串是二进制形式，所以用replace()替换为空
        # 3.又由于这样替换之后是七位，而正常情况下每个字符由8位二进制组成，将其填充为8位
        bytes = bytes + (bin(s[i]).replace('0b', '')
                         ).zfill(8)  # s[i]为该位置字符的十进制表示的ascll码

    f.closed
    return bytes


def add_head(bytes):
    lenth = len(bytes)
    bytes = (bin(lenth).replace('0b', '')).zfill(32) + bytes
    return bytes


im = Image.open(fileMedium)
# 获取文件长宽
width = im.size[0]
height = im.size[1]

# 打开要隐藏的文件，用bytes流存储
bytes = get_bytes(fileHide)
# 给bytes流添加头部，说明bytes流的长度，方便提取
bytes = add_head(bytes)
# 获取最终长度 用于循环
lenth = len(bytes)

cnt = 0

for h in range(0, height):
    for w in range(0, width):
        # 获得(w,h)点像素的值
        pixel = im.getpixel((w, h))
        R = pixel[0]  # R
        G = pixel[1]  # G
        B = pixel[2]  # B
        # 此处，依次从R、G、B修改个颜色通道获得最低位的隐藏信息
        if cnt < lenth:
            R = (R >> 1 << 1) + int(bytes[cnt])  # R
            cnt += 1
        if cnt < lenth:
            G = (G >> 1 << 1) + int(bytes[cnt])  # G
            cnt += 1
        if cnt < lenth:
            B = (B >> 1 << 1) + int(bytes[cnt])  # B
            cnt += 1
        # 修改完后存回去
        im.putpixel((w, h), (R, G, B))
        if cnt == lenth:
            break
    if cnt == lenth:
        break
    
# 隐藏完毕后保存图片
im.save("out.png")
