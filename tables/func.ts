function test() {
	print("yah-fricken-hoo");
}
function test2() {
	return "yabba-dabba";
}

test();
print(test2());

f = test;
f();

print("pass by value?");


function a(m)
{

	m["value"] = 2;
}

m = { "value" : 1 };
print(m["value"]);
a(m);
print(m["value"]);


print("+=?");

a = 0;
print(a);
a += 5;
print(a);

m = { "value" : 0 };
print(m["value"]);
m["value"] += 5;
print(m["value"]);

print("OO?");

function myClass_initialize( self )
{

	self["whatever"] = 127;
}

function myClass_doStuff( self, param1 )
{

	self["whatever"] += param1;
}

function myClass_new()
{

	return {
			"initialize" : myClass_initialize,
			"doStuff" : myClass_doStuff
	};
}

m = myClass_new();
m["initialize"](m);
print(m["whatever"]);

m["doStuff"](m, 373);
print(m["whatever"]);
