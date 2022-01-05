# Daerck's fork of [dwm](https://dwm.suckless.org/).

## Patches

- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/).
- [alternativetags](https://dwm.suckless.org/patches/alternativetags/).
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/).
- [attachaside](https://dwm.suckless.org/patches/attachaside/).
- [hide\_vacant\_tags](https://dwm.suckless.org/patches/hide_vacant_tags/).
- [layoutmenu](https://dwm.suckless.org/patches/layoutmenu/).
- [noborder](https://dwm.suckless.org/patches/noborder/).
- [shiftview](https://lists.suckless.org/dev/1104/7590.html).
- [statuscmd](https://dwm.suckless.org/patches/statuscmd/).
- [sticky](https://dwm.suckless.org/patches/sticky/).
- [swallow](https://dwm.suckless.org/patches/swallow/).
- [taglines](https://github.com/Daerckdev/dwm/blob/master/patches/dwm-taglines-6.2.diff) - This patch is created by me (inspired by [underlinetags](https://dwm.suckless.org/patches/underlinetags/)).
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/).
- [Xresources](https://dwm.suckless.org/patches/xresources/).

## How to install

### Dependency

This build of dwm does not block color emoji in the statusbar, so you must install [libxft-bgra](https://gitlab.freedesktop.org/xorg/lib/libxft), otherwise dwm will crash upon trying to render one.

### Installation

Clone the repository:

```
git clone https://github.com/Daerckdev/dwm
```

Compile and install:

```
cd dwm
sudo make install
```

Finally put "[dwm\_layoutmenu.sh](https://github.com/Daerckdev/dwm/blob/master/dwm_layoutmenu.sh)" in the PATH.

If you use a __display manager__ you also have to do:

```
sudo make xsession
```


