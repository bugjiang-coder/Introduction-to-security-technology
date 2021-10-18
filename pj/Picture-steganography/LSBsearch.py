from PIL import Image

strb = ""
strans = ""
im = Image.open(
    "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\Figure2-encode.png")

width = im.size[0]
height = im.size[1]

print("width:" + str(width))
print("height:" + str(height))

count = 0

for h in range(0, height):
    for w in range(0, width):
        # 获得(w,h)点像素的值

        pixel = im.getpixel((w, h))
        # 此处，依次从R、G、B、A四个颜色通道获得最低位的隐藏信息
        R = pixel[0]  # R
        G = pixel[1]  # G
        B = pixel[2]  # B
        A = pixel[3]  # A

        strb = strb + str(R % 2) + str(G % 2) + str(B % 2) + str(A % 2)


for i in range(0, len(strb), 8):
    # 以每8位为一组二进制，转换为十进制
    strans += chr(int(strb[i:i + 8], 2))

print(strans)

