class MyPrototype {
  public primative: any;
  public component: object;
  public circularReference: ComponentWithBackReference;

  public clone(): this {
    const clone = Object.create(this)

    clone.component = Object.create(this.component)

    clone.circularReference = {
      ...this.circularReference,
      prototype: {...this}
    }

    return clone;
  }
  public traverseProperties(): void {
    console.log(this.primative)
    console.log(this.component)
  }
}

class ComponentWithBackReference {
  public prototype;

  constructor(prototype: MyPrototype) {
    this.prototype = prototype
  }
}

function clientCode() {
  const p1 = new MyPrototype()
  p1.primative = 245
  p1.component = new Date()
  p1.circularReference = new ComponentWithBackReference(p1)

  const p2 = p1.clone()

  console.log("----p1----")
  p1.traverseProperties()
  console.log("----p2----")
  p2.traverseProperties()

  const p3 = Object.assign(p1)

  console.log("----p3----")
  p3.traverseProperties()


  if(p1.primative === p2.primative) {
    console.log("YESSS, value have been carried over to a clone.")
  }
  else console.log("primative field values have not been copied.")
  if(p1.component === p2.component) console.log("cant be cloned")
  else console.log("YESSS, its cloned")

  if(p1.circularReference === p2.circularReference) console.log("compoent with back reference has not been cloned.")
  else console.log("YESSS, component with back reference has been cloned.")

  if(p1.circularReference.prototype === p2.circularReference.prototype) console.log("component with back reference is linked to original object")
  else console.log("YESSS, component with back reference is linked to the clone.")
}

clientCode()