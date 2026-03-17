abstract class MethodSignatures {

  // ─── 1. Basic def ─────────────────────────────────────────────────────────────

  def greet1(): Unit                                      // no params, returns Unit
  def greet2(): Unit = println("Hello")                   // with body
  def add(x: Int, y: Int): Int = x + y                  // two params, explicit return type
  def double(x: Int) = x * 2                            // inferred return type (Int)


  // ─── 2. No-arg / parameterless ───────────────────────────────────────────────

  def version: String = "2.13"                          // no parens — signals pure/stable
  def size(): Int = buffer.length                        // parens — signals side-effect


  // ─── 3. Default parameters ───────────────────────────────────────────────────

  def connect(host: String = "localhost", port: Int = 8080): Unit = ???
  def log(msg: String, level: String = "INFO", ts: Long = System.currentTimeMillis()): Unit = ???


  // ─── 4. Named arguments (caller side, any order) ────────────────────────────

  connect(port = 9090, host = "0.0.0.0")


  // ─── 5. Multiple parameter lists ─────────────────────────────────────────────

  def fold(init: Int)(f: (Int, Int) => Int): Int = ???  // curried
  def using[A](r: AutoCloseable)(body: => A): A = ???   // separate resource & thunk
  def tag(open: String)(content: String)(close: String) = s"$open$content$close"


  // ─── 6. Varargs ───────────────────────────────────────────────────────────────

  def sum(xs: Int*): Int = xs.sum
  def printAll(sep: String, values: String*): Unit = println(values.mkString(sep))

  // passing a Seq as vararg
  val nums = Seq(1, 2, 3)
  sum(nums: _*)


  // ─── 7. By-name parameters ───────────────────────────────────────────────────

  def retry(n: Int)(block: => Unit): Unit =             // block evaluated lazily each call
    (1 to n).foreach(_ => block)

  def unless(cond: Boolean)(action: => Unit): Unit =
    if (!cond) action


  // ─── 8. Implicit parameters ──────────────────────────────────────────────────

  def fetch(url: String)(implicit ec: ExecutionContext): Future[String] = ???
  def serialize[A](a: A)(implicit enc: Encoder[A]): String = enc.encode(a)

  // Scala 2.13 shorthand via context bounds
  def serialize2[A: Encoder](a: A): String = implicitly[Encoder[A]].encode(a)


  // ─── 9. Type parameters & bounds ─────────────────────────────────────────────

  def identity[A](a: A): A = a                          // unconstrained
  def max[A <: Comparable[A]](a: A, b: A): A = ???      // upper bound
  def wrap[A >: Int](a: A): List[A] = List(a)           // lower bound
  def copy[A <: AnyRef](a: A): A = ???                  // reference type only
  def clamp[A: Ordering](v: A, lo: A, hi: A): A = ???   // context bound


  // ─── 10. Multiple type params + variance positions ───────────────────────────

  def zip[A, B](as: List[A], bs: List[B]): List[(A, B)] = as.zip(bs)
  def convert[A, B <: A](list: List[B]): List[A] = list.map(identity)
  def transform[F[_], A, B](fa: F[A])(f: A => B): F[B] = ???  // higher-kinded


  // ─── 11. Function / lambda parameters ────────────────────────────────────────

  def applyTwice(f: Int => Int, x: Int): Int = f(f(x))
  def pipeline[A, B, C](f: A => B, g: B => C): A => C = f andThen g
  def on[A](xs: List[A], pred: A => Boolean): List[A] = xs.filter(pred)


  // ─── 12. Tuple parameters ────────────────────────────────────────────────────

  def swap[A, B](pair: (A, B)): (B, A) = (pair._2, pair._1)
  def addPair(t: (Int, Int)): Int = t._1 + t._2


  // ─── 13. Abstract, override, final ──────────────────────────────────────────

  abstract class Base {
    def process(x: Int): Int                            // abstract
    def describe: String = "Base"                       // concrete
  }

  class Child extends Base {
    override def process(x: Int): Int = x * 2          // override
    override final def describe: String = "Child"       // final — can't override further
  }


  // ─── 14. Access modifiers ────────────────────────────────────────────────────

  class MyClass {
    def pub(x: Int): Int = x                            // public (default)
    private def priv(x: Int): Int = x                  // class-private
    protected def prot(x: Int): Int = x                // class + subclasses
    private[app] def pkgPriv(x: Int): Int = x          // visible within package `app`
    protected[this] def selfOnly(x: Int): Int = x      // only `this` instance
  }


  // ─── 15. Operators as method names ───────────────────────────────────────────

  class Vec(val x: Double, val y: Double) {
    def +(other: Vec): Vec = Vec(x + other.x, y + other.y)
    def *(scalar: Double): Vec = Vec(x * scalar, y * scalar)
    def unary_- : Vec = Vec(-x, -y)
  }


  // ─── 16. Recursive & tail-recursive ──────────────────────────────────────────

  def factorial(n: Int): Int =
    if (n <= 1) 1 else n * factorial(n - 1)


  def factTail(n: Int, acc: Int = 1): Int =
    if (n <= 1) acc else factTail(n - 1, acc * n)


  // ─── 17. Inline / macro-like annotations ─────────────────────────────────────

   final def square(x: Int): Int = x * x        // hint JIT to inline
  def negate[A](x: A): A = ??? // specialise bytecode


  // ─── 18. Returning functions (partial application) ──────────────────────────

  def multiplier(factor: Int): Int => Int = _ * factor
  def adder(a: Int)(b: Int): Int = a + b
  val add5: Int => Int = adder(5)                       // partially applied


  // ─── 19. Throws annotation (Java interop) ────────────────────────────────────


  def sqrt(n: Double): Double =
    if (n < 0) throw new IllegalArgumentException(s"negative: $n")
    else math.sqrt(n)
}

