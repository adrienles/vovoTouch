# Fonts
---
This project utilizes [Apple's SF Compact Rounded font](https://devimages-cdn.apple.com/design/resources/download/SF-Compact.dmg), in 24 pt Semibold variants and 16 and 24 pt Bold variants.
## Generate fonts
1. [Download the font](https://devimages-cdn.apple.com/design/resources/download/SF-Compact.dmg) and install it.
2. Find the corresponding `.otf` files, and run them through an otf to ttf converter.
3. [Generate the fonts](https://lvgl.io/tools/fontconverter) in 4 bpp with the corresponding names:
- sf_comp_round_semibold_24.c
- sf_comp_round_bold_16.c
- sf_comp_round_bold_24.c
- sf_comp_round_bold_48.c (+ and -)
> Note: This is the character set I used when generating mine: QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?èéêëÈÉÊËùúûÙÚÛòóôÒÓÔàáâÀÁÂçÇ
4. Add the font files to this directory.
