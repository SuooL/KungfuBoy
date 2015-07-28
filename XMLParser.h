/*!
 * \file XmlParser.h
 * \date 2015/05/30 11:21
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef __XMLParser_H__
#define __XMLParser_H__

#pragma once

#include <string>
#include "cocos2d.h"

class XMLParser : public cocos2d::Ref, public cocos2d::SAXDelegator
{
public:
	// 解析指定的xml文件
	static XMLParser* parseWithFile(const char *xmlFileName);

	static XMLParser* parseWithString(const char *content);

	XMLParser();
	virtual ~XMLParser();

	// 从本地xml文件读取
	bool initWithFile(const char *xmlFileName);
	// 从字符中读取，可用于读取网络中的xml数据
	bool initWithString(const char *content);

	// 对应xml标签开始,如：<string name="app_name">
	virtual void startElement(void *ctx, const char *name, const char **atts);

	// 对应xml标签结束,如：</string>
	virtual void endElement(void *ctx, const char *name);

	// 对应xml标签文本
	virtual void textHandler(void *ctx, const char *s, int len);

	// 获取对应标签的字符串
	cocos2d::String* getString(const char *key);

private:
	cocos2d::CCDictionary *m_pDictionary;
	std::string m_key;

	std::string startXMLElement;
	std::string endXMLElement;

};

#endif