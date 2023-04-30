interface MyIterator<T> {
  current(): T;
  next(): T;
  key(): number;
  valid(): boolean;
  rewind(): void;
}

interface Aggregator {
  getIterator(): MyIterator<string>;
}

class AlphabeticalOrderIterator implements MyIterator<string> {
  private collection: WordsCollection;
  private position: number = 0;
  private reverse: boolean = false;

  constructor(collection: WordsCollection, reverse: boolean = false) {
    this.collection = collection;
    this.reverse = reverse;
    if(reverse) {
      this.position = collection.getCount() - 1;

    }
  }

  public rewind() {
    this.position = this.reverse ? this.collection.getCount()-1 : 0;

  }
  public current() {
    return this.collection.getItems()[this.position];
  }
  public key() {
    return this.position;
  }

  public next(): string {
    const item = this.collection.getItems()[this.position];
    this.position += this.reverse ? -1 : 1;
    return item;
  }

  public valid() {
    if(this.reverse) return this.position >= 0;
    return this.position < this.collection.getCount();
  }
}

class WordsCollection implements Aggregator {
  private items : string[] = [];
  public getItems(): string[] {
    return this.items;
  }
  public getCount(): number {
    return this.items.length;
  }
  public addItem(item: string): void {
    this.items.push(item);
  }
  public getIterator(): MyIterator<string> {
    return new AlphabeticalOrderIterator(this);
  }
  public getReverseIterator(): MyIterator<string> {
    return new AlphabeticalOrderIterator(this, true);
  }
}

const collection = new WordsCollection();
collection.addItem("first");
collection.addItem("second");
collection.addItem("third");

const iterator = collection.getIterator();

console.log("straight traversal: ");
while(iterator.valid()){
  console.log(iterator.current());
  iterator.next();
}

const reverseItr = collection.getReverseIterator();
reverseItr.rewind();
console.log(`\nreverse traversal: `)
while(reverseItr.valid()){
  console.log(reverseItr.current());
  reverseItr.next();
}

