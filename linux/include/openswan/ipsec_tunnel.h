/*
 * IPSEC tunneling code
 * Copyright (C) 1996, 1997  John Ioannidis.
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003  Richard Guy Briggs.
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
 * RCSID $Id: ipsec_tunnel.h,v 1.33 2005/06/04 16:06:05 mcr Exp $
 */


# define DEV_QUEUE_XMIT(skb, device, pri) {\
	skb->dev = device; \
	neigh_compat_output(skb); \
	/* skb->dst->output(skb); */ \
 }
# define ICMP_SEND(skb_in, type, code, info, dev) \
	icmp_send(skb_in, type, code, htonl(info))
# define IP_SEND(skb, dev) \
	ip_send(skb);


#if defined(KLIPS)
/*
 * Heavily based on drivers/net/new_tunnel.c.  Lots
 * of ideas also taken from the 2.1.x version of drivers/net/shaper.c
 */

struct ipsectunnelconf
{
	__u32	cf_cmd;
	union
	{
		char 	cfu_name[12];
	} cf_u;
#define cf_name cf_u.cfu_name
};

#define IPSEC_SET_DEV	(SIOCDEVPRIVATE)
#define IPSEC_DEL_DEV	(SIOCDEVPRIVATE + 1)
#define IPSEC_CLR_DEV	(SIOCDEVPRIVATE + 2)
#define IPSEC_UDP_ENCAP_CONVERT	(SIOCDEVPRIVATE + 3)
#endif

#ifdef __KERNEL__
#include <linux/version.h>
#ifndef KERNEL_VERSION
#  define KERNEL_VERSION(x,y,z) (((x)<<16)+((y)<<8)+(z))
#endif
struct ipsecpriv
{
	struct sk_buff_head sendq;
	struct net_device *dev;
	struct wait_queue *wait_queue;
	char locked;
	int  (*hard_start_xmit) (struct sk_buff *skb,
		struct net_device *dev);
	int  (*set_mac_address)(struct net_device *dev, void *addr);

	struct net_device_stats *(*get_stats)(struct net_device *dev);
	struct net_device_stats mystats;
	int mtu;	/* What is the desired MTU? */
};

extern char ipsec_tunnel_c_version[];

extern struct net_device *ipsecdevices[IPSEC_NUM_IF];

int ipsec_tunnel_init_devices(void);

/* void */ int ipsec_tunnel_cleanup_devices(void);

extern /* void */ int ipsec_init(void);

extern int ipsec_tunnel_start_xmit(struct sk_buff *skb, struct net_device *dev);
extern struct net_device *ipsec_get_device(int inst);

#ifdef CONFIG_KLIPS_DEBUG
extern int debug_tunnel;
extern int sysctl_ipsec_debug_verbose;
#endif /* CONFIG_KLIPS_DEBUG */
#endif /* __KERNEL__ */

#ifdef CONFIG_KLIPS_DEBUG
#define DB_TN_INIT	0x0001
#define DB_TN_PROCFS	0x0002
#define DB_TN_XMIT	0x0010
#define DB_TN_OHDR	0x0020
#define DB_TN_CROUT	0x0040
#define DB_TN_OXFS	0x0080
#define DB_TN_REVEC	0x0100
#define DB_TN_ENCAP     0x0200
#endif /* CONFIG_KLIPS_DEBUG */

// manage ipsec xmit state objects
extern int ipsec_xmit_state_cache_init (void);
extern void ipsec_xmit_state_cache_cleanup (void);

