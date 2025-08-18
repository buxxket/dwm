# dwm - buxxket's build
## Installation

Run the following in your terminal

```
git clone https://github.com/buxxket/dwm
cd dwm
```

In the `dwm` folder, create file `fonts.h` with:

```
# Adjust to your font
static const char *fonts[] = { "JetBrainsMono Nerd Font:size=10" };
```

Then run 

```
sudo make clean install
```

## patches applied:
* [bartoggle keybinds](https://dwm.suckless.org/patches/bartoggle/)
* [bulkill](https://dwm.suckless.org/patches/bulkill/)
* [colorbar](https://dwm.suckless.org/patches/colorbar/)
* [fixmultimon](https://dwm.suckless.org/patches/fixmultimon/)
* [focusfullscreen](https://dwm.suckless.org/patches/focusfullscreen/)
* [focusmaster-return](https://dwm.suckless.org/patches/focusmaster/)
* [focusmonmouse](https://dwm.suckless.org/patches/focusmonmouse/)
* [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
* [preventfocusshift](https://dwm.suckless.org/patches/preventfocusshift/)
* [restartsig](https://dwm.suckless.org/patches/restartsig/)
* [spawntag](https://dwm.suckless.org/patches/spawntag/)
* [stacker](https://dwm.suckless.org/patches/stacker/)
* [statuscmd](https://dwm.suckless.org/patches/statuscmd/)
* [sticky](https://dwm.suckless.org/patches/sticky/)
* [swallow](https://dwm.suckless.org/patches/swallow/)
* [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
* [xrdb](https://dwm.suckless.org/patches/xrdb/)
* [attach-aside](https://dwm.suckless.org/patches/attachaside/)
