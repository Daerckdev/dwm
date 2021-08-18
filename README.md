# Daerck's fork of [dwm](https://dwm.suckless.org/).

## Patches

- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/).
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/).
- [attachaside](https://dwm.suckless.org/patches/attachaside/).
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/).
- [layoutmenu](https://dwm.suckless.org/patches/layoutmenu/).
- [shiftview](https://lists.suckless.org/dev/1104/7590.html).
- [statuscmd](https://dwm.suckless.org/patches/statuscmd/).
- [sticky](https://dwm.suckless.org/patches/sticky/).
- [swallow](https://dwm.suckless.org/patches/swallow/).
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/).
- [Xresources](https://dwm.suckless.org/patches/xresources/).

## Installation guide

### Dependency

This build of dwm does not block color emoji in the statusbar, so you must install [libxft-bgra](https://gitlab.freedesktop.org/xorg/lib/libxft), otherwise dwm will crash upon trying to render one.

After install all the dependencies:

```
git clone https://github.com/Daerckdev/dwm
cd dwm
sudo make clean install
```

Then put "[dwm\_layoutmenu.sh](https://github.com/Daerckdev/dwm/blob/master/dwm_layoutmenu.sh)" in the PATH.

