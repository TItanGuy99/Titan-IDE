/usr/bin/touch /var/lib/texmf/postinstall/texlive-collection-latex_rm.lsr
/usr/bin/updmap-sys --nohash --nomkmap \
--disable charter.map \
--disable fpls.map \
--disable pazo.map \
--disable utopia.map \

/usr/bin/fmtutil-sys --disablefmt latex/pdftex
/usr/bin/fmtutil-sys --disablefmt pdflatex/pdftex
/usr/bin/fmtutil-sys --disablefmt dvilualatex/luatex
/usr/bin/fmtutil-sys --disablefmt lualatex/luatex
/usr/bin/fmtutil-sys --disablefmt mptopdf/pdftex
/usr/libexec/update_tlpdb remove \
ae \
amscls \
amsmath \
babel-english \
babel \
babelbib \
carlisle \
collection-latex \
colortbl \
dvisvgm-def \
fancyhdr \
fix2col \
geometry \
graphics-cfg \
graphics \
hyperref \
latex-bin.doc \
latex-bin.i386-cygwin \
latex-bin \
latex-bin.x86_64-cygwin \
latex-fonts \
latex \
latexconfig \
ltxmisc \
mfnfss \
mptopdf.doc \
mptopdf.i386-cygwin \
mptopdf \
mptopdf.x86_64-cygwin \
natbib \
oberdiek \
pdftex-def \
pslatex \
psnfss \
pspicture \
tools \
url \

