// Abstract base
abstract class Shape(val color: String) {
  def area: Double
  def perimeter: Double
  override def toString: String =
    f"${getClass.getSimpleName}($color, area=$area%.2f)"
}

// Traits
trait Drawable {
  def draw(): Unit = println(s"Drawing: $this")
}

trait Resizable {
  def scale(factor: Double): Shape
}

// Sealed hierarchy (ADT-style)
sealed abstract class Polygon(color: String) extends Shape(color) with Drawable with Resizable

final class Circle(color: String, val radius: Double)
  extends Shape(color) with Drawable with Resizable {
  def area: Double      = Math.PI * radius * radius
  def perimeter: Double = 2 * Math.PI * radius
  def scale(f: Double): Circle = new Circle(color, radius * f)
}

final class Rectangle(color: String, val width: Double, val height: Double)
  extends Polygon(color) {
  def area: Double      = width * height
  def perimeter: Double = 2 * (width + height)
  def scale(f: Double): Rectangle = new Rectangle(color, width * f, height * f)
}

final class EquilateralTriangle(color: String, val side: Double)
  extends Polygon(color) {
  def area: Double      = (Math.sqrt(3) / 4) * side * side
  def perimeter: Double = 3 * side
  def scale(f: Double): EquilateralTriangle = new EquilateralTriangle(color, side * f)
}

// Companion + factory
object Shape {
  def apply(kind: String, color: String, dims: Double*): Shape = kind match {
    case "circle"   => new Circle(color, dims(0))
    case "rect"     => new Rectangle(color, dims(0), dims(1))
    case "triangle" => new EquilateralTriangle(color, dims(0))
    case other      => throw new IllegalArgumentException(s"Unknown shape: $other")
  }
}

// Case class variant
case class Point(x: Double, y: Double)

// Usage
object TheApp extends App {
  val shapes: List[Shape with Drawable] = List(
    new Circle("red", 5),
    new Rectangle("blue", 4, 6),
    new EquilateralTriangle("green", 3)
  )

  shapes.foreach { s =>
    s.draw()
    println(f"  perimeter = ${s.perimeter}%.2f")
  }

  // Exhaustive match on sealed hierarchy
  def describe(p: Polygon): String = p match {
    case r: Rectangle           => s"Rectangle ${r.width}x${r.height}"
    case t: EquilateralTriangle => s"Triangle side=${t.side}"
  }

  val scaled = new Rectangle("blue", 4, 6).scale(2.0)
  println(describe(scaled)) // Rectangle 8.0x12.0

  // Factory
  val c = Shape("circle", "yellow", 7.0)
  println(c)
}