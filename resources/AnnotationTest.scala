import scala.annotation._
import scala.annotation.meta._
import scala.beans.{BeanProperty, BooleanBeanProperty}

// ─── 1. CUSTOM ANNOTATIONS ──────────────────────────────────────────────────

class threadSafe                      extends StaticAnnotation
class since(version: String)          extends StaticAnnotation
class tag(name: String)               extends StaticAnnotation
class doc(text: String)               extends StaticAnnotation

@field  class fieldOnly(v: String)    extends StaticAnnotation
@getter class getterOnly(v: String)   extends StaticAnnotation
@param  class paramOnly(v: String)    extends StaticAnnotation

// ─── 2. CLASSFILE-RETAINED ANNOTATION ───────────────────────────────────────

class audit(user: String) extends ClassfileAnnotation

// ─── 3. @implicitNotFound ───────────────────────────────────────────────────

@implicitNotFound("No Encoder for type ${A}. Derive or implement one.")
trait Encoder[A] {
  def encode(a: A): String
}

// ─── 4. BODY ────────────────────────────────────────────────────────────────

object Annotations {

  // @deprecated
  @deprecated("Use newFoo instead", since = "2.1.0")
  def oldFoo(): Unit = println("old")
  def newFoo(): Unit = println("new")

  // @deprecatedName
  def greet(@deprecatedName(Symbol("nm"), "1.5") name: String): String =
    s"Hello, $name"

  // @inline / @noinline
  @inline   final def add(a: Int, b: Int): Int = a + b
  @noinline def debug(msg: String): Unit        = println(msg)

  // @tailrec
  def factorial(n: Int): BigInt = {
    @tailrec
    def loop(acc: BigInt, n: Int): BigInt =
      if (n <= 0) acc else loop(acc * n, n - 1)
    loop(1, n)
  }

  // @switch — all branches must be int literals
  def describe(x: Int): String = (x: @switch) match {
    case 0 => "zero"
    case 1 => "one"
    case 2 => "two"
    case _ => "other"
  }

  // @unchecked — suppress exhaustiveness warning
  def unsafeHead(list: List[Int]): Int = (list: @unchecked) match {
    case h :: _ => h
  }

  // @throws — checked exception declaration for Java interop
  @throws(classOf[IllegalArgumentException])
  def divide(a: Int, b: Int): Int = {
    if (b == 0) throw new IllegalArgumentException("div by zero")
    a / b
  }

  // @specialized — generate primitive bytecode variants
  class Box[@specialized(Int, Double) A](val value: A)

  // @transient / @volatile — JVM field modifiers (only valid on var)
  class Cache {
    @transient @volatile private var _cache: Map[String, Int] = Map.empty
    @volatile            private var _ready: Boolean           = false
  }

  // @SerialVersionUID
  @SerialVersionUID(42L)
  class Payload(val data: String) extends Serializable

  // ─── BEAN ANNOTATIONS ─────────────────────────────────────────────────────

  class Person(@BeanProperty var name: String,
               @BooleanBeanProperty var active: Boolean)
  // Generates: getName/setName, isActive/setActive

  // ─── META-ANNOTATIONS ─────────────────────────────────────────────────────

  class Entity(
                @(since @field)("1.0")    // annotation targets the backing field
                val id: Long,
                @(since @getter)("1.0")   // annotation targets the accessor method
                val name: String
              )

  // ─── RUNTIME REFLECTION ───────────────────────────────────────────────────

  class MyService {
    @doc("Fetches a user by id")
    @since("1.0")
    @threadSafe
    def getUser(id: Int): String = s"user-$id"
    // StaticAnnotation is erased at runtime — getAnnotations returns []
    // Use ClassfileAnnotation (below) for runtime visibility
  }

  // ─── CLASSFILE-RETAINED ANNOTATION ────────────────────────────────────────

  class BillingService {
    @audit(user = "system")           // visible via reflection at runtime
    def charge(amount: Double): Unit = println(s"charging $amount")
  }

  // ─── ANNOTATION ON VARIOUS POSITIONS ──────────────────────────────────────

  @threadSafe                         // class
  class Counter {

    @volatile private var count = 0   // field (must be var)

    @inline
    def increment(): Unit = count += 1

    def reset(@deprecatedName(Symbol("v"), "2.0") value: Int = 0): Unit =
      count = value

    @threadSafe                       // nested object
    object Stats { def current: Int = count }
  }

  @threadSafe                         // object
  object GlobalCounter extends Counter

  @since("1.0")                       // trait
  trait Resettable { def reset(): Unit }

  // ─── TYPE ANNOTATIONS ─────────────────────────────────────────────────────

  def process(xs: List[Int @unchecked]): Int = xs.sum

  // ─── @implicitNotFound in action ──────────────────────────────────────────

  implicit val intEncoder: Encoder[Int] = (a: Int) => a.toString

  def serialize[A](a: A)(implicit enc: Encoder[A]): String = enc.encode(a)
  // serialize("hi")  // ← compile error: No Encoder for type String. Derive or implement one.
}

// ─── DEMO ────────────────────────────────────────────────────────────────────

object Demo extends App {
  import Annotations._

  println(factorial(10))          // 3628800
  println(describe(1))            // one
  println(divide(10, 2))          // 5

  val p = new Person("Alice", active = true)
  println(p.getName)              // Alice
  println(p.isActive)             // true

  println(serialize(42))          // 42

  val svc = new MyService
  println(svc.getUser(1))         // user-1

  // StaticAnnotation → erased; ClassfileAnnotation → retained
  val m1 = classOf[MyService].getMethod("getUser", classOf[Int])
  println(s"MyService annotations:     ${m1.getAnnotations.toList}")   // []

  val m2 = classOf[BillingService].getMethod("charge", classOf[Double])
  println(s"BillingService annotations: ${m2.getAnnotations.toList}")  // [@audit(...)]
}