#include <stdlib.h>
#include <stdio.h>

#include "XvcArglist.h"
#include "XvcCleanup.h"
#include "XvcFunctionId.h"
#include "XvcTree.h"

static void debug_report(const char * function, void * address)
{
	if (!address) {
		printf("[NULL]:      %s\n", function);
	}
	else {
		printf("%p: %s\n", address, function);
	}
}

struct TreeList {
	struct TreeList * next;
	XvcTree * tree;
};

struct ArglistList { // Yeah, I know.
	struct ArglistList * next;
	XvcArglist * item;
};

struct IdList {
	struct IdList * next;
	char * item;
};


static struct TreeList * DanglingTrees = NULL;
static struct ArglistList * DanglingArglists = NULL;
static struct IdList * DanglingIds = NULL;

void print_tree_list();
void print_arglist_list();
void print_id_list();

void XvcCleanupClearAll()
{
	XvcCleanupClearTrees();
	XvcCleanupClearArglists();
	XvcCleanupClearFunctionIds();
}

void print_tree_list()
{
	struct TreeList * CurrentNode;
	CurrentNode = DanglingTrees;
	while (CurrentNode) {
		printf("%p: Cached Tree\n", CurrentNode->tree);
		CurrentNode = CurrentNode->next;
	}
}

void print_arglist_list()
{
	struct ArglistList * CurrentNode;
	CurrentNode = DanglingArglists;
	while (CurrentNode) {
		printf("%p: Cached Arglist\n", CurrentNode->item);
		CurrentNode = CurrentNode->next;
	}
}

void print_id_list()
{
	struct IdList * CurrentNode;
	CurrentNode = DanglingIds;
	while (CurrentNode) {
		printf("%p: Cached FunctionId\n", CurrentNode->item);
		CurrentNode = CurrentNode->next;
	}
}


void XvcCleanupCacheTree(XvcTree * in)
{
	//debug_report(__FUNCTION__, in);
	struct TreeList * NewNode;
	struct TreeList * CurrentNode;
	NewNode = malloc(sizeof(struct TreeList));
	NewNode->tree = in;
	NewNode->next = NULL;
	//printf("NewNode: %p t:%p n:%p\n", NewNode, NewNode->tree, NewNode->next);

	if (!DanglingTrees) {
		DanglingTrees = NewNode;
		//printf("!DT so DT becomes: %p\n", DanglingTrees);
	}
	else {
		CurrentNode = DanglingTrees;
		while (CurrentNode->next) {
			CurrentNode = CurrentNode->next;
		}
		CurrentNode->next = NewNode;
		//printf("Appending %p to %p.\n", NewNode, CurrentNode);
	}
	//print_tree_list();
}

void XvcCleanupReleaseTree(XvcTree * in)
{
	//debug_report(__FUNCTION__, in);
	struct TreeList ** ParentPointer;
	struct TreeList * CurrentNode;

	if (!DanglingTrees) {
		//printf("!Dangling Tree, so not removing anything.\n");
		return;
	}

	CurrentNode = DanglingTrees;
	ParentPointer = &DanglingTrees;
	
	//printf("ParentPointer(%p), CurrentNode(%p)\n", ParentPointer, DanglingTrees);
	while (CurrentNode) {
		if (CurrentNode->tree == in) {
			//printf("Found %p in %p. Deleting!\n", in, CurrentNode);
			*ParentPointer = CurrentNode->next;
			free(CurrentNode);
			CurrentNode = *ParentPointer;
		}
		else {
			ParentPointer = &(CurrentNode->next);
			CurrentNode = *ParentPointer;
		}
	}
}

void XvcCleanupClearTrees()
{
	//debug_report(__FUNCTION__, NULL);
	struct TreeList * CurrentNode;
	struct TreeList * OldNode;

	CurrentNode = DanglingTrees;
	DanglingTrees = NULL;
	
	while (CurrentNode) {
		//printf("Deleting: %p t:%p n:%p\n", CurrentNode, CurrentNode->tree, CurrentNode->next);
		XvcTreeDelete(CurrentNode->tree);
		OldNode = CurrentNode;
		CurrentNode = CurrentNode->next;
		free(OldNode);
	}
}

//////////////////////////////////////////////////////////////////////////////

void XvcCleanupCacheArglist(XvcArglist * in)
{
	//debug_report(__FUNCTION__, in);
	struct ArglistList * NewNode;
	struct ArglistList * CurrentNode;
	NewNode = malloc(sizeof(struct ArglistList));
	NewNode->item = in;
	NewNode->next = NULL;
	//printf("NewNode: %p t:%p n:%p\n", NewNode, NewNode->item, NewNode->next);

	if (!DanglingArglists) {
		DanglingArglists = NewNode;
		//printf("!DT so DT becomes: %p\n", DanglingTrees);
	}
	else {
		CurrentNode = DanglingArglists;
		while (CurrentNode->next) {
			CurrentNode = CurrentNode->next;
		}
		CurrentNode->next = NewNode;
		//printf("Appending %p to %p.\n", NewNode, CurrentNode);
	}
	//print_tree_list();
}

void XvcCleanupReleaseArglist(XvcArglist * in)
{
	//debug_report(__FUNCTION__, in);
	struct ArglistList ** ParentPointer;
	struct ArglistList * CurrentNode;

	if (!DanglingArglists) {
		//printf("!Dangling Tree, so not removing anything.\n");
		return;
	}

	CurrentNode = DanglingArglists;
	ParentPointer = &DanglingArglists;
	
	//printf("ParentPointer(%p), CurrentNode(%p)\n", ParentPointer, DanglingTrees);
	while (CurrentNode) {
		if (CurrentNode->item == in) {
			//printf("Found %p in %p. Deleting!\n", in, CurrentNode);
			*ParentPointer = CurrentNode->next;
			free(CurrentNode);
			CurrentNode = *ParentPointer;
		}
		else {
			ParentPointer = &(CurrentNode->next);
			CurrentNode = *ParentPointer;
		}
	}
}

void XvcCleanupClearArglists()
{
	//debug_report(__FUNCTION__, NULL);
	struct ArglistList * CurrentNode;
	struct ArglistList * OldNode;

	CurrentNode = DanglingArglists;
	DanglingArglists = NULL;
	
	while (CurrentNode) {
		//printf("Deleting: %p t:%p n:%p\n", CurrentNode, CurrentNode->tree, CurrentNode->next);
		XvcArglistDelete(CurrentNode->item);
		OldNode = CurrentNode;
		CurrentNode = CurrentNode->next;
		free(OldNode);
	}
}

//////////////////////////////////////////////////////////////////////////////

void XvcCleanupCacheFunctionId(char * in)
{
	//debug_report(__FUNCTION__, in);
	struct IdList * NewNode;
	struct IdList * CurrentNode;
	NewNode = malloc(sizeof(struct IdList));
	NewNode->item = in;
	NewNode->next = NULL;
	//printf("NewNode: %p t:%p n:%p\n", NewNode, NewNode->item, NewNode->next);

	if (!DanglingIds) {
		DanglingIds = NewNode;
		//printf("!DT so DT becomes: %p\n", DanglingTrees);
	}
	else {
		CurrentNode = DanglingIds;
		while (CurrentNode->next) {
			CurrentNode = CurrentNode->next;
		}
		CurrentNode->next = NewNode;
		//printf("Appending %p to %p.\n", NewNode, CurrentNode);
	}
	//print_tree_list();
}

void XvcCleanupReleaseFunctionId(char * in)
{
	//debug_report(__FUNCTION__, in);
	struct IdList ** ParentPointer;
	struct IdList * CurrentNode;

	if (!DanglingIds) {
		//printf("!Dangling Tree, so not removing anything.\n");
		return;
	}

	CurrentNode = DanglingIds;
	ParentPointer = &DanglingIds;
	
	//printf("ParentPointer(%p), CurrentNode(%p)\n", ParentPointer, DanglingTrees);
	while (CurrentNode) {
		if (CurrentNode->item == in) {
			//printf("Found %p in %p. Deleting!\n", in, CurrentNode);
			*ParentPointer = CurrentNode->next;
			free(CurrentNode);
			CurrentNode = *ParentPointer;
		}
		else {
			ParentPointer = &(CurrentNode->next);
			CurrentNode = *ParentPointer;
		}
	}
}

void XvcCleanupClearFunctionIds()
{
	//debug_report(__FUNCTION__, NULL);
	struct IdList * CurrentNode;
	struct IdList * OldNode;

	CurrentNode = DanglingIds;
	DanglingIds = NULL;
	
	while (CurrentNode) {
		//printf("Deleting: %p t:%p n:%p\n", CurrentNode, CurrentNode->tree, CurrentNode->next);
		XvcFunctionIdDelete(CurrentNode->item);
		OldNode = CurrentNode;
		CurrentNode = CurrentNode->next;
		free(OldNode);
	}
}
