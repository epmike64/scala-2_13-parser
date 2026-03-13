class TupleTest {
  // ── 1. Basic tuple destructuring ─────────────────────────────────────────
  val (a1, b1)       = (1, 2)
  val (x1, y1, z1)    = (1, 2, 3)

  // ── 2. With explicit type annotation ─────────────────────────────────────
  val (a2: Int, b2: String) = (42, "hello")

  // ── 3. Discarding elements with _ ────────────────────────────────────────
  val (first, _, third) = (1, 2, 3)
  val (_, second)       = (10, 20)

  // ── 4. Nested tuples ─────────────────────────────────────────────────────
  val ((a3, b3), c3)  = ((1, 2), 3)
  val (a, (b4, c4))  = (1, (2, 3))

  // ── 5. var tuple destructuring ───────────────────────────────────────────
  var (x, y) = (1, 2)
  x = 10     // only individual vars are reassignable, not the tuple itself

  // ── 6. From a method returning a tuple ───────────────────────────────────
  def minMax(xs: List[Int]): (Int, Int) = (xs.min, xs.max)

  val (lo, hi)     = minMax(List(3, 1, 4, 1, 5))

  // ── 7. In a for-comprehension ─────────────────────────────────────────────
  val pairs1 = List((1, "one"), (2, "two"), (3, "three"))

  for ((n, s) <- pairs1) println(s"$n -> $s")

  val doubled = for ((k, v) <- Map("a" -> 1, "b" -> 2)) yield k -> v * 2

  // ── 8. match / pattern matching ──────────────────────────────────────────
  val t = (42, "hello", true)
  t match {
    case (n, s, true)  => println(s"flag set: $n $s")
    case (n, s, false) => println(s"flag off: $n $s")
  }

  // ── 9. As lambda parameter (partial function) ────────────────────────────
  val pairs2 = List((1, 2), (3, 4))

  pairs2.map { case (a, b) => a + b }        // case required for tuple unpack
  pairs2.foreach { case (k, v) => println(k -> v) }

  // ── 10. Swap via tuple ────────────────────────────────────────────────────
  var (p, q) = (1, 2)
  val tmp = p;  // classic way
  // idiomatic Scala:
  val (p2, q2) = (q, p)                     // new bindings, swapped

  // ── 11. Chained / aliased with @ ──────────────────────────────────
}
