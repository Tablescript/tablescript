
OBJS = 	AssignmentExpression.o \
		BinaryExpression.o \
		Block.o \
		BreakStatement.o \
		Builtins.o \
		CallExpression.o \
        Class.o \
        ClassStatement.o \
		ConditionalExpression.o \
		ContinueStatement.o \
		Dice.o \
		DiceLiteral.o \
		ElementExpression.o \
		Error.o \
        ExitStatement.o \
		Expression.o \
		ExpressionStatement.o \
		Float.o \
		FloatLiteral.o \
		ForStatement.o \
		Function.o \
		FunctionStatement.o \
		Identifier.o \
		IfStatement.o \
		ImportStatement.o \
		IncDecExpression.o \
        Instance.o \
		Integer.o \
		IntegerLiteral.o \
		Interpreter.o \
		LHSObject.o \
		List.o \
		ListLiteral.o \
		Map.o \
		MapLiteral.o \
        MemberExpression.o \
        MethodExpression.o \
		None.o \
		NoneLiteral.o \
		Object.o \
		ReturnStatement.o \
		Scope.o \
		Statement.o \
		String.o \
		StringLiteral.o \
		Table.o \
		TableEntry.o \
		TableStatement.o \
		Translate.o \
		UnaryExpression.o \
		WhileStatement.o

CC = g++
CCFLAGS = -g -c -Wall

all: $(OBJS)

.cpp.o:
	$(CC) $(CCFLAGS) $<

clean:
	rm -f *.o
	rm -f *~

