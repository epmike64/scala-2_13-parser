class Employee(
    plainId: Int,                    // constructor parameter only, not a field
    val firstName: String,           // public read-only field
    var department: String,          // public mutable field
    private val ssn: String,         // private read-only field
    private var salary: Double       // private mutable field
) {

  // class body members: these become fields/members of the instance
  val company: String = "Acme Corp"         // public field
  var level: Int = 1                        // public mutable field
  private val createdBy: String = "system"  // private field
  private var active: Boolean = true        // private mutable field

  // computed member, method not field
  def fullName: String = s"$firstName [$department]"

  // can access plain constructor parameter inside class methods
  def employeeId: Int = plainId

  def currentSalary: Double = salary

  def giveRaise(amount: Double): Unit = {
    val oldSalary = salary        // local variable, not a field
    salary = salary + amount
    println(s"Salary changed from $oldSalary to $salary")
  }

  def promote(newLevel: Int, newDepartment: String): Unit = {
    level = newLevel
    department = newDepartment
  }

  def deactivate(): Unit = {
    active = false
  }

  def isActive: Boolean = active

  private def audit(): String = {
    s"createdBy=$createdBy, ssn=$ssn"
  }

  def debugInfo(): String = {
    val temp = audit()   // local variable
    s"id=$plainId, name=$firstName, dept=$department, level=$level, $temp"
  }

  // auxiliary constructor
  def this(firstName: String) = {
    this(0, firstName, "Unassigned", "N/A", 0.0)
    println("Auxiliary constructor used")
  }
}

object EmployeeDemo {
  def main(args: Array[String]): Unit = {
    val e1 = new Employee(101, "Mike", "Trading", "111-22-3333", 120000.0)

    println(e1.firstName)      // OK: val field
    println(e1.department)     // OK: var field
    e1.department = "Risk"     // OK: mutable field
    println(e1.company)        // OK: class-body val
    e1.level = 2               // OK: class-body var

    println(e1.employeeId)     // accesses plain constructor param through method
    println(e1.fullName)

    e1.giveRaise(5000.0)
    e1.promote(3, "Architecture")
    println(e1.debugInfo())

    val e2 = new Employee("John")
    println(e2.fullName)
  }
}