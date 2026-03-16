
// ─── 1. Package declaration ───────────────────────────────────────────────────

// Standard top-level package
package com.example.app

// Chained (nested) package — equivalent to package com { package example { ... } }
package com.example
package app




// ─── 2. Basic imports ─────────────────────────────────────────────────────────

import scala.collection.mutable.ListBuffer       // single class
import java.util.{List, Map, HashMap}            // multi-import (selector)
import scala.util._                              // wildcard
import scala.concurrent.{Future, Promise, _}     // mixed: named + wildcard
import scala.concurrent.ExecutionContext.Implicits.global   // implicit ExecutionContext
import scala.language.implicitConversions                   // enable implicit conversions
import scala.language.postfixOps                           // enable postfix syntax (1 to 10 toList)

// ─── 3. Renaming on import ────────────────────────────────────────────────────

import java.util.{List => JList, Map => JMap}    // rename to avoid collision
import scala.collection.immutable.{List => SList}


// ─── 4. Hiding on import ──────────────────────────────────────────────────────

import java.util.{Date => _, _}                  // import all java.util except Date
import scala.collection.mutable.{Set => _, _}    // hide mutable.Set, import rest
import alg.{Ring, Field}                         // import path-dependent types

import scala.math.{Pi, sqrt, abs}               // object members as functions/values
import java.lang.Math.{PI, sin, cos}
import util.StringUtils    // resolves to com.example.app.util.StringUtils (relative)
import _root_.com.other.Lib  // _root_ forces absolute path from root package


