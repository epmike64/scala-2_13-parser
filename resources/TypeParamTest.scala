import scala.collection.mutable

// ── 1. Simple generic class ───────────────────────────────────────────────────
class Box[A](val value: A) {
  import com1.test1.Tester1
  def map[B](f: A => B): Box[B] = new Box(f(value))
  override def toString: String = s"Box($value)"
}

import com2.test2.Tester2

// ── 2. Context bound: A must have an implicit Ordering ───────────────────────
class SortedPair[A: Ordering](val first: A, val second: A) {
  private val ord = implicitly[Ordering[A]]
  def min: A = if (ord.lt(first, second)) first else second
  def max: A = if (ord.gt(first, second)) first else second
  override def toString: String = s"SortedPair($first, $second)"
}

// ── 3. Lower bound ───────────────────────────────────────────────────────────
class Stack[A] {
  import com3.test3.Tester3

  private val elems: mutable.ListBuffer[A] = mutable.ListBuffer.empty

  def push(x: A): this.type = { elems.prepend(x); this }
  def pop(): Option[A]      = if (elems.isEmpty) None else Some(elems.remove(0))
  def peek: Option[A]       = elems.headOption

  // B >: A — accept supertypes when widening the stack type
  def pushAll[B >: A](xs: Seq[B]): Stack[B] = {
    import com4.test4.Tester4
    val s = new Stack[B]
    xs.foreach(s.push)
    s
  }

  override def toString: String = s"Stack(${elems.mkString(", ")})"
}

// ── 4. Multiple type parameters + variance ───────────────────────────────────
class Pair[+A, +B](val fst: A, val snd: B) {
  def swap: Pair[B, A]          = new Pair(snd, fst)
  def mapFst[C](f: A => C): Pair[C, B] = new Pair(f(fst), snd)
  def mapSnd[C](f: B => C): Pair[A, C] = new Pair(fst, f(snd))
  override def toString: String = s"Pair($fst, $snd)"
}

// ── 5. Context bound: A must have an implicit Ordering ───────────────────────
class PriorityBag[A: Ordering] {
  private val ord: Ordering[A]        = implicitly[Ordering[A]]
  private val buf: mutable.ListBuffer[A] = mutable.ListBuffer.empty

  def add(x: A): Unit    = buf += x
  def takeMin(): Option[A] = {
    if (buf.isEmpty) None
    else {
      val m = buf.min(ord)
      buf -= m
      Some(m)
    }
  }
  override def toString: String = s"PriorityBag(${buf.mkString(", ")})"
}

// ── 6. Generic trait + abstract type member hybrid ───────────────────────────
trait Container[F[_]] {
  def wrap[A](a: A): F[A]
  def unwrap[A](fa: F[A]): A
}

object OptionContainer extends Container[Option] {
  def wrap[A](a: A): Option[A]   = Some(a)
  def unwrap[A](fa: Option[A]): A = fa.get
}

// ── 7. Recursive type parameter (F-bounded) ───────────────────────────────────
abstract class Animal[A <: Animal[A]] {
  def name: String
  def copy(): A
}

class Dog(val name: String) extends Animal[Dog] {
  def copy(): Dog = new Dog(name)
  override def toString: String = s"Dog($name)"
}

class Cat(val name: String) extends Animal[Cat] {
  def copy(): Cat = new Cat(name)
  override def toString: String = s"Cat($name)"
}

// ── Main ──────────────────────────────────────────────────────────────────────
object TypeParamTestApp extends App {

  // 1. Box
  val b = new Box(42)
  println(b.map(_ * 2))           // Box(84)

  // 2. SortedPair (Int has an implicit Ordering in Scala 2.13)
  val sp = new SortedPair[Int](10, 3)
  println(s"min=${sp.min} max=${sp.max}")  // min=3 max=10

  // 3. Stack
  val st = new Stack[Int]
  st.push(1).push(2).push(3)
  println(st)                     // Stack(3, 2, 1)
  println(st.pop())               // Some(3)

  // 4. Pair with covariance
  val p = new Pair("hello", 99)
  println(p.swap)                 // Pair(99, hello)
  println(p.mapSnd(_ + 1))        // Pair(hello, 100)

  // 5. PriorityBag
  val pb = new PriorityBag[Int]
  Seq(5, 1, 3, 2, 4).foreach(pb.add)
  println(pb.takeMin())           // Some(1)
  println(pb.takeMin())           // Some(2)

  // 6. Container
  val wrapped = OptionContainer.wrap(123)
  println(OptionContainer.unwrap(wrapped)) // 123

  // 7. F-bounded
  val d = new Dog("Rex")
  println(d.copy())               // Dog(Rex)
}