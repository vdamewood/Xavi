/*
 * XaviParser.h: Parser for Xavi.
 * Copyright 2014 Vincent Damewood
 *
 * This file is part of Xavi.
 *
 * Xavi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Xavi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Xavi. If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined XAVI_PARSER_H
#define XAVI_PARSER_H

#include "SyntaxTree.hpp"
#include "Lexer.hpp"

namespace Xavi
{
	class InfixParser
	{
	public:
		InfixParser(Xavi::Lexer *NewLexer);
		~InfixParser(void);
		void Parse(void);
		SyntaxTreeNode &SyntaxTree(void);
	private:
		Xavi::SyntaxTreeNode *GetExpr0(void);
		Xavi::BranchNode     *GetExpr0r(void);
		Xavi::SyntaxTreeNode *GetExpr1(void);
		Xavi::BranchNode     *GetExpr1r(void);
		Xavi::SyntaxTreeNode *GetExpr2(void);
		Xavi::SyntaxTreeNode *GetExpr2lf(void);
		Xavi::SyntaxTreeNode *GetExpr3(void);
		Xavi::SyntaxTreeNode *GetExpr3lf(void);
		Xavi::SyntaxTreeNode *GetAtom(void);
		Xavi::SyntaxTreeNode *GetNumber(void);
		Xavi::SyntaxTreeNode *GetUNumber(void);
		Xavi::SyntaxTreeNode *GetFCall(void);
		Xavi::BranchNode     *GetArguments(void);

		Lexer *MyLexer;
		SyntaxTreeNode *MySyntaxTree;
	};
};
#endif /* XAVI_PARSER_H */