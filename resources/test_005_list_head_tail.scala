class ListHeadTailAssignmentTest {

  // ── 1. Head / tail split ──────────────────────────────────────────────────
  val h :: t        = List(1, 2, 3)     // h = 1, t = List(2, 3)
  val head :: tail1  = List(1, 2, 3)

  // ── 2. First N elements ───────────────────────────────────────────────────
  val a1 :: b1 :: rest1      = List(1, 2, 3, 4)   // a=1, b=2, rest=List(3,4)
  val a2 :: b2 :: c2 :: rest2 = List(1, 2, 3, 4)   // a=1, b=2, c=3, rest=List(4)

  // ── 3. Exact length match ─────────────────────────────────────────────────
  val List(x, y, z) = List(1, 2, 3)   // fails at runtime if size != 3

  // ── 4. Discarding with _ ──────────────────────────────────────────────────
  val _ :: second :: _ = List(1, 2, 3)   // second = 2
  val _ :: tail        = List(1, 2, 3)   // skip head

  // ── 5. match – the safe way ───────────────────────────────────────────────
  List(1, 2, 3) match {
    case Nil              => println("empty")
    case h :: Nil         => println(s"singleton: $h")
    case h :: t           => println(s"head=$h tail=$t")
  }

  // ── 6. Nested head/tail ───────────────────────────────────────────────────
  List(List(1, 2), List(3, 4)) match {
    case (a :: b :: Nil) :: rest => println(s"a=$a b=$b rest=$rest")
    case _                       => println("other")
  }

  // ── 7. Matching last element ──────────────────────────────────────────────
  def lastElem[A](xs: List[A]): A = xs match {
    case x :: Nil  => x
    case _ :: tail => lastElem(tail)
    case Nil       => throw new NoSuchElementException
  }

  // ── 8. Matching specific values ───────────────────────────────────────────
  List(0, 1, 2) match {
    case 0 :: rest  => println(s"starts with zero, rest=$rest")
    case _          => println("other")
  }

  // ── 9. for-comprehension with guard ──────────────────────────────────────
  val lists = List(List(1,2), Nil, List(3,4))

  for (h :: t <- lists) println(s"head=$h")   // skips Nil automatically

  // ── 10. @ to capture sub-list ─────────────────────────────────────────────
  List(1, 2, 3, 4) match {
    case h :: (rest @ (_ :: _ :: _)) => println(s"h=$h rest=$rest")  // rest has 2+
    case h :: rest                   => println(s"short tail")
  }

  // ── 11. Recursive processing pattern ─────────────────────────────────────
  def sum(xs: List[Int]): Int = xs match {
    case Nil       => 0
    case h :: tail => h + sum(tail)
  }

  // ── 12. Collect head of each sub-list ────────────────────────────────────
  val nested = List(List(1, 2), List(3, 4), List(5, 6))
  val heads  = nested.collect { case h :: _ => h }   // List(1, 3, 5)

  // ── 13. takeWhile / span / splitAt (stdlib, not pattern) ─────────────────
  val (evens, rest) = List(2, 4, 5, 6).span(_ % 2 == 0)  // (List(2,4), List(5,6))
  val (front, back) = List(1,2,3,4,5).splitAt(3)          // (List(1,2,3), List(4,5))

}
