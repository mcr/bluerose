/*
 * sysctl interface to net IPSEC subsystem.
 * Copyright (C) 1998, 1999, 2000, 2001	  Richard Guy Briggs.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * RCSID $Id: sysctl_net_ipsec.c,v 1.17.10.2 2007/10/30 21:42:25 paul Exp $
 */

/* -*- linux-c -*-
 *
 * Initiated April 3, 1998, Richard Guy Briggs <rgb@conscoop.ottawa.on.ca>
 */

#include <linux/version.h>
#include <linux/mm.h>
#include <linux/sysctl.h>

#include "openswan/ipsec_param.h"

#ifdef CONFIG_SYSCTL

#define NET_IPSEC   CTL_UNNUMBERED 
                             
#ifdef CONFIG_KLIPS_DEBUG
extern int       debug_ah;
extern int       debug_esp;
extern int       debug_tunnel;
extern int       debug_eroute;
extern int       debug_spi;
extern int       debug_radij;
extern int       debug_netlink;
extern int       debug_xform;
extern int       debug_rcv;
extern int       debug_pfkey;
extern int sysctl_ipsec_debug_verbose;
#ifdef CONFIG_KLIPS_IPCOMP
extern int sysctl_ipsec_debug_ipcomp;
#endif /* CONFIG_KLIPS_IPCOMP */
#endif /* CONFIG_KLIPS_DEBUG */

extern int sysctl_ipsec_icmp;
extern int sysctl_ipsec_inbound_policy_check;
extern int sysctl_ipsec_tos;
int sysctl_ipsec_regress_pfkey_lossage;

enum {
#ifdef CONFIG_KLIPS_DEBUG
	NET_IPSEC_DEBUG_AH=1,
	NET_IPSEC_DEBUG_ESP=2,
	NET_IPSEC_DEBUG_TUNNEL=3,
	NET_IPSEC_DEBUG_EROUTE=4,
	NET_IPSEC_DEBUG_SPI=5,
	NET_IPSEC_DEBUG_RADIJ=6,
	NET_IPSEC_DEBUG_NETLINK=7,
	NET_IPSEC_DEBUG_XFORM=8,
	NET_IPSEC_DEBUG_RCV=9,
	NET_IPSEC_DEBUG_PFKEY=10,
	NET_IPSEC_DEBUG_VERBOSE=11,
	NET_IPSEC_DEBUG_IPCOMP=12,
#endif /* CONFIG_KLIPS_DEBUG */
	NET_IPSEC_ICMP=13,
	NET_IPSEC_INBOUND_POLICY_CHECK=14,
	NET_IPSEC_TOS=15,
	NET_IPSEC_REGRESS_PFKEY_LOSSAGE=16,
};

static ctl_table ipsec_table[] = {
#ifdef CONFIG_KLIPS_DEBUG
       { .ctl_name = NET_IPSEC_DEBUG_AH,
         .procname = "debug_ah",
         .data     = &debug_ah,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_ESP,
         .procname = "debug_esp",
         .data     = &debug_esp,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_TUNNEL,
         .procname = "debug_tunnel",
         .data     = &debug_tunnel,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_EROUTE,
         .procname = "debug_eroute",
         .data     = &debug_eroute,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_SPI,
         .procname = "debug_spi",
         .data     = &debug_spi,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_RADIJ,
         .procname = "debug_radij",
         .data     = &debug_radij,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_NETLINK,
         .procname = "debug_netlink",
         .data     = &debug_netlink,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_XFORM,
         .procname = "debug_xform",
         .data     = &debug_xform,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_RCV,
         .procname = "debug_rcv",
         .data     = &debug_rcv,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_PFKEY,
         .procname = "debug_pfkey",
         .data     = &debug_pfkey,
          .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

        { .ctl_name = NET_IPSEC_DEBUG_VERBOSE,
         .procname = "debug_verbose",
         .data     = &sysctl_ipsec_debug_verbose,
         .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },
#endif /* CONFIG_KLIPS_DEBUG */

#ifdef CONFIG_KLIPS_IPCOMP
        { .ctl_name = NET_IPSEC_DEBUG_IPCOMP,
         .procname = "debug_ipcomp",
         .data     = &sysctl_ipsec_debug_ipcomp,
         .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },
#endif /* CONFIG_KLIPS_IPCOMP */

#ifdef CONFIG_KLIPS_REGRESS
       {
         .ctl_name = NET_IPSEC_REGRESS_PFKEY_LOSSAGE,
         .procname = "pfkey_lossage",
         .data     = &sysctl_ipsec_regress_pfkey_lossage,
         .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },
#endif /* CONFIG_KLIPS_REGRESS */

       { .ctl_name = NET_IPSEC_ICMP,
         .procname = "icmp",
         .data     = &sysctl_ipsec_icmp,
         .maxlen   = sizeof(int),
         .mode     = 0644,
         .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

       { .ctl_name = NET_IPSEC_INBOUND_POLICY_CHECK,
         .procname = "inbound_policy_check",
         .data     = &sysctl_ipsec_inbound_policy_check,
          .maxlen   = sizeof(int),
          .mode     = 0644,
          .child    = NULL,
         .proc_handler = &proc_dointvec,
       },

       { .ctl_name = NET_IPSEC_TOS,
          .procname = "tos",
          .data     = &sysctl_ipsec_tos,
          .maxlen   = sizeof(int),
          .mode     = 0644,
          .child    = NULL,
          .proc_handler = &proc_dointvec,
       },
       {0}
};

static ctl_table ipsec_net_table[] = {
	{ .ctl_name = NET_IPSEC,
          .procname = "ipsec",
          .data     = NULL,
          .maxlen   = 0,
          .mode     = 0555,
          .child    = ipsec_table,
          .proc_handler = NULL,
        },
	{ 0 }
};
 
static ctl_table ipsec_root_table[] = {
	{ .ctl_name = CTL_NET,
          .procname = "net",
          .data     = NULL,
          .maxlen   = 0,
          .mode     = 0555,
          .child    = ipsec_net_table,
          .proc_handler = NULL,
        },
	{ 0 }
};

 
static struct ctl_table_header *ipsec_table_header;

int ipsec_sysctl_register(void)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,21)
        ipsec_table_header = register_sysctl_table(ipsec_root_table);
#else
        ipsec_table_header = register_sysctl_table(ipsec_root_table, 0);
#endif
        if (!ipsec_table_header) {
                return -ENOMEM;
	}
        return 0;
}
 
void ipsec_sysctl_unregister(void)
{
        unregister_sysctl_table(ipsec_table_header);
}

#endif /* CONFIG_SYSCTL */

