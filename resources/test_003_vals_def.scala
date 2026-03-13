
// ── 4. Declaration only (abstract – inside trait/abstract class) ──────────
trait Foo {
  val required: Int          // abstract val
  var mutable: String        // abstract var
  def compute: Double        // abstract def (not a var, but same idea)
}

object Main {


  def main(args: Array[String]): Unit = {


    // ── 1. val – immutable binding (like final in Java) ──────────────────────
    val x: Int = 42
    val y       = 42          // type inferred

    // ── 2. var – mutable binding ──────────────────────────────────────────────
    var counter: Int = 0
    var name         = "foo"  // inferred as String

    // ── 3. lazy val – evaluated once, on first access ─────────────────────────
    lazy val expensive: String = { println("computed"); "result" }


    // ── 5. Type alias ─────────────────────────────────────────────────────────
    type Id    = Long
    type Table = Map[String, List[Int]]

    // ── 6. Tuple destructuring ────────────────────────────────────────────────
    val (a, b)    = (1, 2)
    val (p, _, r) = (10, 20, 30)   // _ discards middle

    // ── 7. Case class / pattern destructuring ────────────────────────────────
    case class Point(x: Int, y: Int)
    val Point(px, py) = Point(3, 4)

    // ── 8. Multiple assignment via pattern ───────────────────────────────────
    val h :: t  = List(1, 2, 3)   // h = 1, t = List(2,3)

    // ── 9. Local def (method as value) ───────────────────────────────────────
    def double(n: Int): Int = n * 2

    // ── 10. Function value (eta-expansion / lambda) ──────────────────────────
    val double2: Int => Int  = n => n * 2
    val double3              = (n: Int) => n * 2  // inferred
    val double4: Int => Int  = _ * 2              // placeholder syntax

    // ── 11. By-name parameter (declaration context) ──────────────────────────
    def run(block: => Unit): Unit = block   // block is unevaluated until called

    // ── 12. implicit val / var ───────────────────────────────────────────────
    implicit val ordering: Ordering[Int] = Ordering.Int

    // ── 13. final val (compile-time constant) ────────────────────────────────

  }
}

