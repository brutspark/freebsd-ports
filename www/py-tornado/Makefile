# Created by: Guixing Bai <khsing.cn@gmail.com>
# $FreeBSD$

PORTNAME=	tornado
PORTVERSION=	5.0.2
CATEGORIES=	www python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	gblach@FreeBSD.org
COMMENT=	Python Web Server from FriendFeed

LICENSE=	APACHE20

CONFLICTS=	py[0-9]*-tornado4-*

USES=		python
USE_PYTHON=	autoplist distutils

.include <bsd.port.pre.mk>

.if ${PYTHON_REL} < 3400
RUN_DEPENDS+=	${PYTHON_PKGNAMEPREFIX}singledispatch>0:devel/py-singledispatch@${FLAVOR}
.endif

.if ${PYTHON_REL} < 3500
RUN_DEPENDS+=	${PYTHON_PKGNAMEPREFIX}backports_abc>=0.4:devel/py-backports_abc@${FLAVOR}
.endif

post-build:
	@${FIND} ${WRKSRC}/build -name speedups.so -exec ${STRIP_CMD} {} \;

regression-test: build
	@cd ${WRKSRC} && ${PYTHON_CMD} -m tornado.test.runtests

.include <bsd.port.post.mk>
