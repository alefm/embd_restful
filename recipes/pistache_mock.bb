DESCRIPTION = "Mock pistache web framework"
HOMEPAGE = "https://github.com/alefm/embd_restful"
LICENSE = "LGPL-2.1"
LIC_FILES_CHKSUM = "file://../LICENSE;md5=103dec6c7ab3d2eb3c46bf9850092c30"

inherit cmake pkgconfig
SRC_URI = "git://github.com/alefm/embd_restful"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git/pistache-mock"

DEPENDS = "pistache jansson sqlite3"
RDEPENDS_${PN} = "pistache jansson sqlite3"

do_install() {
  install -d ${D}${bindir}
  install -m 0755 pistache-mock ${D}${bindir}
}
