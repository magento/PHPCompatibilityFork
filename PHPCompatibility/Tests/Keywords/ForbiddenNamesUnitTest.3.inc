<?php

/*
 * Test a number of specific code constructs and that errors are thrown on the correct line.
 */

// Test multiple errors for multiple incorrect namespace parts, as well as tolerance for comments and whitespace.
namespace For\ List /*comment*/ \Foreach ?><?php // Error x3.

// Test multi-use line precision, including `as` as alias.
use My\Foo as As, // Error.
    My\Bar as Private; // Error.

// Test multi-line group use with multiple imports & line precision.
use My\{
    FooBar as Or, // Error.
    function bar as list, // Error.
    const BAZ as DIE, // Error.
};

class Foo {
    // Test trait method aliases with visibility modifiers.
    // Note: tests with _only_ the modifiers, without alias, are included in the `1.inc` file.
    use FooTraitPublic {
        oldFunctionA as public endWhile; // Error.
        oldFunctionB as public public; // Error.
    }
    use FooTraitProtected {
        oldFunctionA as protected endFor; // Error.
        oldFunctionB as protected protected; // Error.
    }
    use FooTraitPrivate {
        oldFunctionA as private endSwitch; // Error.
        oldFunctionB as private private; // Error.
    }
    use FooTraitFinal {
        oldFunctionA as final endDeclare; // Error.
        oldFunctionB as final final; // Error.
    }

    // Test trait use with multiple statements, including `as` as alias.
    use BazTrait {
        oldfunctionA as private as; // Error.
        oldfunctionB as final finally; // Error.
        oldfunctionC as public; // OK.
        oldfunctionD as as; // Error.
    }

    // Test `class` as class constant name.
    const class = 1; // Error.

    // Test nested functions. These are declared in the global namespace and should comply with those rules.
    function baz() {
        function exit() {} // Error.
    }

    // Test calls to define() with comments in the name parameter.
    function bal() {
        define(
            /*comment*/
            'interface' /*comment*/,
            1
        ); // Error.
    }
}

trait FooTrait {
    // Test trait using other traits.
    use A, B {
        A::bigTalk insteadof B;
        B::bigTalk as Switch; // Error.
    }
}

// Test function delared to return by reference.
function &trait() {}