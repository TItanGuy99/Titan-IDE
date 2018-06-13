/usr/bin/touch /var/lib/texmf/postinstall/texlive-collection-basic_rm.lsr
/usr/bin/updmap-sys --nohash --nomkmap \
--disable cm.map \
--disable cmextra.map \
--disable cyrillic.map \
--disable euler.map \
--disable latxfont.map \
--disable symbols.map \
--disable cmtext-bsr-interpolated.map \
--disable dummy-space.map \
--disable mathpple.map \

/usr/bin/fmtutil-sys --disablefmt luatex/luatex
/usr/bin/fmtutil-sys --disablefmt dviluatex/luatex
/usr/bin/fmtutil-sys --disablefmt luajittex/luajittex
/usr/bin/fmtutil-sys --disablefmt mf/mf-nowin
/usr/bin/fmtutil-sys --disablefmt pdftex/pdftex
/usr/bin/fmtutil-sys --disablefmt etex/pdftex
/usr/bin/fmtutil-sys --disablefmt pdfetex/pdftex
/usr/bin/fmtutil-sys --disablefmt tex/tex
/usr/libexec/update_tlpdb remove \
amsfonts \
bibtex.i386-cygwin \
bibtex \
bibtex.x86_64-cygwin \
cm \
collection-basic \
dvipdfmx-def \
dvipdfmx.i386-cygwin \
dvipdfmx \
dvipdfmx.x86_64-cygwin \
dvips.i386-cygwin \
dvips \
dvips.x86_64-cygwin \
enctex \
etex-pkg \
etex \
glyphlist \
gsftopk.i386-cygwin \
gsftopk \
gsftopk.x86_64-cygwin \
hyph-utf8 \
hyphen-base \
ifluatex \
ifxetex \
knuth-lib \
knuth-local \
kpathsea.i386-cygwin \
kpathsea \
kpathsea.x86_64-cygwin \
lua-alt-getopt \
luatex.i386-cygwin \
luatex \
luatex.x86_64-cygwin \
makeindex.i386-cygwin \
makeindex \
makeindex.x86_64-cygwin \
metafont.i386-cygwin \
metafont \
metafont.x86_64-cygwin \
mflogo \
mfware.i386-cygwin \
mfware \
mfware.x86_64-cygwin \
pdftex.i386-cygwin \
pdftex \
pdftex.x86_64-cygwin \
plain \
tetex.i386-cygwin \
tetex \
tetex.x86_64-cygwin \
tex-ini-files.doc \
tex-ini-files \
tex.doc \
tex.i386-cygwin \
tex \
tex.x86_64-cygwin \
texconfig.doc \
texconfig.i386-cygwin \
texconfig \
texconfig.x86_64-cygwin \
texlive-common \
texlive-docindex \
texlive-en \
texlive-msg-translations \
texlive-scripts.i386-cygwin \
texlive-scripts \
texlive-scripts.x86_64-cygwin \
texlive.infra.doc \
texlive.infra.i386-cygwin \
texlive.infra \
texlive.infra.x86_64-cygwin \
unicode-data \
updmap-map \
xdvi.i386-cygwin \
xdvi \
xdvi.x86_64-cygwin \

