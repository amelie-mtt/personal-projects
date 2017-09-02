#ifndef ADMIN_H
#define ADMIN_H


typedef enum Direction_t Direction;

extern void AdminUI_init(void);
extern void AdminUI_start(void);
extern void Admin_free(void);
extern	void askMvt(Direction dir);
extern	void ask4Log(void);
extern	void askClearLog();
extern	void quit();


#endif
//
