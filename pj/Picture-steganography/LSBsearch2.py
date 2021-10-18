from PIL import Image


#  来自PIL import image
#  image = Image.open（"test.png"）
#  image_out = Image.new（image.mode，image.size）

#  pixels = list（image.getdata（））
#  image_out.putdata（pixels）
#  image_out.save（'test_out.png'）

strb = ""
strans = ""
im = Image.open(
    "D:\workspace\Introduction-to-security-technology\pj\Picture-steganography\Figure3-origin.png")

width = im.size[0]
height = im.size[1]

print("width:" + str(width))
print("height:" + str(height))


H_im= Image.new("RGB", (width, height))
L_im= Image.new("RGB", (width, height))

for h in range(0, height):
    for w in range(0, width):
        # 获得(w,h)点像素的值

        pixel = im.getpixel((w, h))
        # print(pixel)
        # break
        # 此处，依次从R、G、B修改个颜色通道获得最低位的隐藏信息
        R = pixel[0]  # R
        G = pixel[1]  # G
        B = pixel[2]  # B

        R_H = (R >> 4) << 4
        G_H = (G >> 4) << 4
        B_H = (B >> 4) << 4

        R_L = R & 0xf
        G_L = G & 0xf
        B_L = B & 0xf

        H_im.putpixel((w, h), (R_H, G_H, B_H))
        L_im.putpixel((w, h), (R_L, G_L, B_L))
    
    print(h)

H_im.save("H.png")
L_im.save("L.png")
