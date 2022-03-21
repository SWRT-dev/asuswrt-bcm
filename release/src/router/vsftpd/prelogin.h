/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef VSF_PRELOGIN_H
#define VSF_PRELOGIN_H

struct vsf_session;

/* init_connection()
 * PURPOSE
 * Called as an entry point to FTP protocol processing, when a client connects.
 * This function will emit the FTP greeting, then start talking FTP protocol
 * to the client.
 * PARAMETERS
 * p_sess         - the current session object
 */
void init_connection(struct vsf_session* p_sess);

#endif /* VSF_PRELOGIN_H */
