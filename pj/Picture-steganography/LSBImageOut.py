from PIL import Image
import struct

fileAnalysis = "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\out.png"


# 把读取出的数据写入文件中
def out_file(bytes):
    f = open("find.png", "wb")  # 要读取二进制文件，比如图片、视频等等，用'rb'模式打开文件
    for x in bytes:
        a = struct.pack('B', x)
        f.write(a)
    f.close()


def get_bytes(lenth, im):
    cnt = 0
    bytes = ""
    width = im.size[0]
    height = im.size[1]
    for h in range(0, height):
        for w in range(0, width):
            # 获得(w,h)点像素的值
            pixel = im.getpixel((w, h))
            R = pixel[0]  # R
            G = pixel[1]  # G
            B = pixel[2]  # B
            # 此处，依次从R、G、B修改个颜色通道获得最低位的隐藏信息
            if cnt < lenth:
                bytes += str(R % 2)  # R
                cnt += 1
            if cnt < lenth:
                bytes += str(G % 2)  # G
                cnt += 1
            if cnt < lenth:
                bytes += str(B % 2)  # B
                cnt += 1

            if cnt == lenth:
                break
        if cnt == lenth:
            break
    return bytes


im = Image.open(fileAnalysis)
# 获取隐写文件长度
lenth = int(get_bytes(32, im), 2)
# 读取隐写文件
bytes = ""
bytes = get_bytes(32+lenth, im)[32:]

# 将隐写文件装换为比特流
fileBytes = []
for i in range(0, len(bytes), 8):
    # 以每8位为一组二进制，转换为十进制
    fileBytes.append(int(bytes[i:i + 8], 2))

# 输出文件
out_file(fileBytes)
