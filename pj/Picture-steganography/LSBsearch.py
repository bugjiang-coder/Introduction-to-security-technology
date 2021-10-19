from PIL import Image

# 存放提取的bite流
bytes = ""
# 存放提取结果
ans = ""
# 实验一图片
fileName = "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\Figure2-encode.png"

# 打开要提取的图片
im = Image.open(fileName)
# 获取图片的长宽
width = im.size[0]
height = im.size[1]


for h in range(0, height):
    for w in range(0, width):
        # 获得(w,h)点像素的值
        pixel = im.getpixel((w, h))
        # 此处，依次从R、G、B、A四个颜色通道获得最低位的隐藏信息
        R = pixel[0]  # R
        G = pixel[1]  # G
        B = pixel[2]  # B
        A = pixel[3]  # A
        # 将每个像素的最后一位顺序存储到bytes中
        bytes = bytes + str(R % 2) + str(G % 2) + str(B % 2) + str(A % 2)


# 将bytes流以每8位为一组二进制，转换为十进制，再转化为ascii码字符
for i in range(0, len(bytes), 8):
    ans += chr(int(bytes[i:i + 8], 2))

# 打印结果
print(ans)
