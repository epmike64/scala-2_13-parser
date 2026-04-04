object ForExamples extends App {

  def section(title: String): Unit = println(s"\n=== $title ===")

  // 1. Basic iteration
  section("1. Basic iteration")
  for (i <- 1 to 5) print(s"$i ")
  println()
  for (i <- 1 until 5) print(s"$i ")
  println()
  for (i <- 1 to 10 by 2) print(s"$i ")
  println()
  for (i <- 10 to 1 by -1) print(s"$i ")
  println()

  // 2. Collection iteration
  section("2. Collection iteration")
  val xs = List("a", "b", "c")
  for (x <- xs) print(s"$x ")
  println()
  for (x <- xs) { val up = x.toUpperCase; print(s"$up ") }
  println()

  // 3. Guards
  section("3. Guards")
  for (i <- 1 to 20 if i % 3 == 0 if i % 5 == 0) print(s"$i ")
  println()
  for (x <- xs if x != "b") print(s"$x ")
  println()

  // 4. Multiple generators
  section("4. Multiple generators")
  for (i <- 1 to 3; j <- 1 to 3) print(s"($i,$j) ")
  println()
  for {
    i <- 1 to 4
    j <- 1 to 4
    if i != j
    if i + j == 5
  } println(s"$i + $j = 5")

  // 5. yield
  section("5. yield")
  val squares = for (i <- 1 to 5) yield i * i
  println(squares)
  val evens = for (i <- 1 to 10 if i % 2 == 0) yield i
  println(evens)
  val mapped: List[String] = for (x <- List(1, 2, 3)) yield x.toString
  println(mapped)

  // 6. Pattern matching in generator
  section("6. Pattern matching in generator")
  val pairs = List((1, "one"), (2, "two"), (3, "three"))
  for ((n, s) <- pairs) println(s"$n -> $s")

  val opts = List(Some(1), None, Some(3))
  for (Some(v) <- opts) print(s"$v ")
  println()

  case class Point(x: Int, y: Int)
  val pts = List(Point(1, 2), Point(3, 4))
  for (Point(x, y) <- pts) println(s"x=$x y=$y")

  // 7. val definitions inside for
  section("7. val inside for")
  for {
    i  <- 1 to 5
    sq  = i * i
    if sq > 5
  } println(s"$i^2 = $sq")

  // 8. Iterating maps
  section("8. Map iteration")
  val m = Map("a" -> 1, "b" -> 2, "c" -> 3)
  for ((k, v) <- m) println(s"$k=$v")
  for ((k, v) <- m if v > 1) print(s"$k ")
  println()

  // 9. Nested yield (flattening)
  section("9. Nested yield / flatten")
  val matrix = List(List(1, 2, 3), List(4, 5, 6))
  val flat = for (row <- matrix; x <- row) yield x
  println(flat)

  // 10. for over Option / Either
  section("10. Option and Either")
  val some15: Option[Int] = for { a <- Some(10); b <- Some(5) } yield a + b
  println(some15)

  val none: Option[Int] = for { a <- Some(10); b <- None: Option[Int] } yield a + b
  println(none)

  val right15: Either[String, Int] = for {
    a <- Right(10): Either[String, Int]
    b <- Right(5):  Either[String, Int]
  } yield a + b
  println(right15)

  val left: Either[String, Int] = for {
    a <- Right(10):   Either[String, Int]
    b <- Left("err"): Either[String, Int]
  } yield a + b
  println(left)
}