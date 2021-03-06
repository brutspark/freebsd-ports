--- net/socket/udp_socket_posix.cc.orig	2018-02-24 16:25:17.000000000 +0100
+++ net/socket/udp_socket_posix.cc	2018-03-04 03:08:15.161087000 +0100
@@ -69,7 +69,7 @@
 const base::TimeDelta kActivityMonitorMsThreshold =
     base::TimeDelta::FromMilliseconds(100);
 
-#if defined(OS_MACOSX) || defined(OS_FUCHSIA)
+#if defined(OS_MACOSX) || defined(OS_FUCHSIA) || defined(OS_BSD)
 
 // When enabling multicast using setsockopt(IP_MULTICAST_IF) MacOS and Fuchsia
 // require passing IPv4 address instead of interface index. This function
@@ -647,13 +647,16 @@
   DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
   int value = broadcast ? 1 : 0;
   int rv;
-#if defined(OS_MACOSX)
+#if defined(OS_MACOSX) || defined(OS_BSD)
   // SO_REUSEPORT on OSX permits multiple processes to each receive
   // UDP multicast or broadcast datagrams destined for the bound
   // port.
   // This is only being set on OSX because its behavior is platform dependent
   // and we are playing it safe by only setting it on platforms where things
   // break.
+  rv = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
+  if (rv != 0)
+    return MapSystemError(errno);
   rv = setsockopt(socket_, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value));
   if (rv != 0)
     return MapSystemError(errno);
@@ -860,19 +863,24 @@
   if (multicast_interface_ != 0) {
     switch (addr_family_) {
       case AF_INET: {
-#if defined(OS_MACOSX) || defined(OS_FUCHSIA)
+#if defined(OS_MACOSX) || defined(OS_FUCHSIA) || defined(OS_BSD)
         ip_mreq mreq;
         int error = GetIPv4AddressFromIndex(socket_, multicast_interface_,
                                             &mreq.imr_interface.s_addr);
         if (error != OK)
           return error;
-#else   //  defined(OS_MACOSX) || defined(OS_FUCHSIA)
+#else   //  defined(OS_MACOSX) || defined(OS_FUCHSIA) || defined(OS_BSD)
         ip_mreqn mreq;
         mreq.imr_ifindex = multicast_interface_;
         mreq.imr_address.s_addr = htonl(INADDR_ANY);
 #endif  //  !defined(OS_MACOSX) && !defined(OS_FUCHSIA)
         int rv = setsockopt(socket_, IPPROTO_IP, IP_MULTICAST_IF,
+#if defined(OS_BSD)
+                            reinterpret_cast<const char*>(&mreq.imr_interface.s_addr),
+                            sizeof(mreq.imr_interface.s_addr));
+#else
                             reinterpret_cast<const char*>(&mreq), sizeof(mreq));
+#endif
         if (rv)
           return MapSystemError(errno);
         break;
@@ -934,7 +942,7 @@
       if (addr_family_ != AF_INET)
         return ERR_ADDRESS_INVALID;
 
-#if defined(OS_MACOSX) || defined(OS_FUCHSIA)
+#if defined(OS_MACOSX) || defined(OS_FUCHSIA) || defined(OS_BSD)
       ip_mreq mreq;
       int error = GetIPv4AddressFromIndex(socket_, multicast_interface_,
                                           &mreq.imr_interface.s_addr);
