import scala.reflect.ClassTag
import scala.concurrent.ExecutionContext

// 1. No parameters
class Foo()
class Foo2  // parens optional if empty

// 2. Plain parameters (not fields)
class Foo3(x: Int, y: String)

// 3. val/var fields
class Foo4(val x: Int, var y: String)

// 4. Default values
class Foo5(val x: Int = 0, val y: String = "default")

// 5. Private constructor
class Foo6 private(val x: Int)

// 6. Access modifier on individual param
class Foo7(val x: Int, private val y: String)

// 7. Implicit parameter list
class Foo8(val x: Int)(implicit val ec: ExecutionContext)

// 8. Multiple parameter lists
class Foo9(val x: Int)(val y: String)

// 9. Type parameters
class Foo10[A, B](val a: A, val b: B)

// 10. Varargs
class Foo11(val xs: Int*)

// 11. By-name parameter
class Foo12(x: => Int)  // rare, but legal


// 13. Case class (compiler generates apply/unapply/copy/equals/hashCode)
case class Foo14(x: Int, y: String)

// 14. Combining several
class Foo15[A](val x: A, private var y: Int = 0)(implicit val tag: ClassTag[A])