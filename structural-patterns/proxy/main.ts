interface Subject {
  request(): void
}

class RealSubject implements Subject {
  public request(): void {
    console.log("RealSubject: handling request.\n")
  }
}

class MyProxy implements Subject {
  private realSubject : RealSubject;

  constructor(realSubject: RealSubject) {
    this.realSubject = realSubject
  }

  public request(): void {
    if(this.checkAccess()) {
      this.realSubject.request();
      this.logAccess();
    }
  }

  private checkAccess(): boolean {
    console.log("proxy: checking access prior to firing a real request.\n")
    return true;
  }

  private logAccess() : void {
    console.log("proxy: logging the time of request.\n")
  } 
}

function clientCode(subject : Subject) {
  subject.request()
}

console.log("Client: executing the client code with real subject.")
const real = new RealSubject();
clientCode(real)

console.log("Client: executing with proxy")
const proxy = new MyProxy(real)
clientCode(proxy)