#ifndef __TOKEN_H
#define __TOKEN_H

#define MAX	1024

int tbfInit(int cps, int burst);

int tbfFetchToken(int tbfId, int fetchTokens);

void tbfDestroy(int tbfId);

void tbfDestroyAll(void);

#endif

