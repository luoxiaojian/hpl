# ######################################################################
#  
#
SHELL            = /bin/sh
#
arch             = UNKNOWN
#
## Targets #############################################################
#
all              : install
#
# ######################################################################
#
install          : startup refresh build
#
startup          :
	$(MAKE) -f Make.top startup_dir     arch=$(arch)
	$(MAKE) -f Make.top startup_src     arch=$(arch)
	$(MAKE) -f Make.top startup_tst     arch=$(arch)
	$(MAKE) -f Make.top refresh_src     arch=$(arch)
	$(MAKE) -f Make.top refresh_tst     arch=$(arch)
#
refresh          :
	$(MAKE) -f Make.top refresh_src     arch=$(arch)
	$(MAKE) -f Make.top refresh_tst     arch=$(arch)
#
build            :
	$(MAKE) -f Make.top build_src       arch=$(arch)
	$(MAKE) -f Make.top build_tst       arch=$(arch)
#
clean            :
	$(MAKE) -f Make.top clean_src       arch=$(arch)
	$(MAKE) -f Make.top clean_tst       arch=$(arch)
#
clean_arch       :
	$(MAKE) -f Make.top clean_arch_src  arch=$(arch)
	$(MAKE) -f Make.top clean_arch_tst  arch=$(arch)
#
clean_arch_all   :
	$(MAKE) -f Make.top clean_arch_all  arch=$(arch)
#
clean_guard      :
	$(MAKE) -f Make.top clean_guard_src arch=$(arch)
	$(MAKE) -f Make.top clean_guard_tst arch=$(arch)
#
# ######################################################################
