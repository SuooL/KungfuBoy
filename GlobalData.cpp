/*!
 * \file  GlobalData.cpp
 * \date  2015/04/18 0:08
 *
 * \author SuooL_振生
 * Blog  suool.net || blog.csdn.net/suool
  * Contact 1020935219@qq.com
 *
 * \brief  多文件共享变量
 *
 * \version 1.0
 *
 * TODO: 
 *
 * \note
*/
#include "GlobalData.h"
#include "Monster.h"

int m_iSelectGate;
bool m_bFlag1;
bool m_bFlag2;
bool m_bFlag3;
bool m_bFlag4;
bool m_bFlag5;

Vector<Monster*> monsterOneList;
Vector<Monster*> monsterTwoList;
Vector<Monster*> monsterThreeList;
Vector<Monster*> monsterFourList;
Vector<Monster*> monsterFiveList;
Vector<Monster*> monsterShowList;