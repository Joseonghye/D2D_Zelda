#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__

enum OBJID{BACKGROUND, PLAYER, MONSTER, INTERACTION,POTAL, WALL, HOLE,ITEM,EVENT,OBJID_END};
enum EVENT { BUTTON, CHECK, CLOSE, ENTER,OPEN, EVENT_END };
enum TEXTYPE {SINGLE, MULTI, TEXTYPE_END};
enum SCENE {TITLE, GAME, SCENE_END};
enum OBJSTATE {NO_EVENT,DEAD, OBJSTATE_END};

enum class COMPONENTID { TRANSFORM, CONTROLLER, RENDER, COLLISION, ANIMATOR, END };

enum STATE { IDLE, WALK, ATTACK, PUSH, DAMAGED,FALL,STATE_END };
enum DIR { FRONT, BACK, LEFT, RIGHT, DIR_END };

#endif //__ENUM_H__