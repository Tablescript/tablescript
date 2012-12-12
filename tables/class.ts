
function globalFunc( wank )
{

    print( "way cool" );
    wank.third();
}

class Wank
{

    function __init__()
    {

    }

    function test()
    {

        print("yah-frickin-hoo");
        this.another();
    }

    function another()
    {

        print("oh baby");
        globalFunc( this );
    }

    function third()
    {

        print( "oh hot damn");
    }

    function withParameters( stringParameter, floatParameter )
    {

        print( stringParameter );
        print( floatParameter );
    }
}

w = Wank();
w.test();
w.withParameters( "abcdef", 3.14159 );

w.memberVar = 12;
print( w.memberVar );

w.newMethod = globalFunc;
w.newMethod( w );


class WithConstructor
{

    function __init__()
    {

        print( "in constructor" );
        this.otherFunc();
    }

    function otherFunc()
    {

        print( "in otherFunc()" );
    }
}

w = WithConstructor();

#q = 12;
#q.noMethod();

