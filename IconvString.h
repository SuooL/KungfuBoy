/*!
 * \file IconvString.h
 * \date 2015/05/30 9:05
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief ×Ö·û±àÂë
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __ICONVSTRING_H__
#define __ICONVSTRING_H__

int convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen);

int gbk2utf8(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

#endif