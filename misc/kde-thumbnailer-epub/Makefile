# $FreeBSD$

PORTNAME=	kde-thumbnailer-epub
PORTVERSION=	1.0
PORTREVISION=	2
CATEGORIES=	misc kde
MASTER_SITES=	http://kde-apps.org/CONTENT/content-files/
DISTNAME=	151210-${PORTNAME}-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	KDE thumbnail generator for ePub files

PORTSCOUT=	limit:^1\.0

USES=		cmake:outsource kde:4
USE_KDE=	kdelibs automoc4
USE_QT4=	moc_build qmake_build rcc_build uic_build
WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}

PLIST_FILES=	lib/kde4/epubthumbnail.so \
		share/kde4/services/epubthumbnail.desktop

.include <bsd.port.mk>
