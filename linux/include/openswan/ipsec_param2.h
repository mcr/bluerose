/*
 * header file for Openswan kernel compat
 * Copyright (C) 2009 Michael Richardson <mcr@sandelman.ca>
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/lgpl.txt>.
 * 
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 */

#ifndef _IPSEC_PARAM2_H_
#define _IPSEC_PARAM2_H_

/* nicely, latest netdevice.h includes this define */
#ifndef HAVE_NETDEV_PRIV
#define netdev_priv(dev) (dev->priv)
#endif

/* kernels > 2.4.2 */
#if defined(IP_SELECT_IDENT) && defined(IP_SELECT_IDENT_NEW)
#define KLIPS_IP_SELECT_IDENT(iph, skb) ip_select_ident(iph, skb_dst(skb), NULL)
#endif



#endif /* _OPENSWAN_PARAM2_H */

