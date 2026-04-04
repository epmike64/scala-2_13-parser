
// ── 1. Auxiliary constructors ─────────────────────────────────────────────
class Point(val x: Double, val y: Double, val label: String) {

  // Auxiliary constructors must delegate to another constructor via this(...)
  def this(x: Double, y: Double) = this(x, y, "unnamed")
  def this(label: String)        = this(0.0, 0.0, label)
  def this()                     = this(0.0, 0.0, "origin")

  override def toString: String = s"$label($x, $y)"
}

// ── 2. Self-reference in methods ──────────────────────────────────────────
class Builder(private var _value: Int = 0) {

  def add(n: Int): this.type = { _value += n; this }  // this.type for fluent chaining
  def mul(n: Int): this.type = { _value *= n; this }
  def build(): Int = _value
}

// ── 3. Self-type annotation (structural requirement, not inheritance) ──────
trait Logging {
  def log(msg: String): Unit = println(s"[LOG] $msg")
}

trait Service { this: Logging =>           // self-type: implementor must also mix in Logging
  def process(x: Int): Int = {
    log(s"processing $x")
    x * 2
  }
}

class ConcreteService extends Service with Logging   // satisfies the self-type requirement

// ── 4. Self-alias (common in cake pattern / complex inner refs) ────────────
class Outer { self =>                      // "self" is just an alias for "this"

  val name = "Outer"

  class Inner {
    // "this" here would refer to Inner; self refers to the Outer instance
    def whoAmI: String = s"Inner inside ${self.name}"
  }
}

// ── Demo ──────────────────────────────────────────────────────────────────
object Main extends App {

  // 1. Auxiliary constructors
  println(new Point(3.0, 4.0, "P"))   // P(3.0, 4.0)
  println(new Point(1.0, 2.0))        // unnamed(1.0, 2.0)
  println(new Point("A"))             // A(0.0, 0.0)
  println(new Point())                // origin(0.0, 0.0)

  // 2. Fluent builder via this.type
  val result = new Builder().add(10).mul(3).add(5).build()
  println(result)                     // 35

  // 3. Self-type
  val svc = new ConcreteService
  println(svc.process(7))             // [LOG] processing 7 \n 14

  // 4. Self-alias
  val outer = new Outer
  val inner = new outer.Inner
  println(inner.whoAmI)               // Inner inside Outer
}