import { Component, OnInit } from '@angular/core';
import { Book } from 'src/app/core/models/book.model';
import { BookService } from 'src/app/core/services/books/book.service';
import { HttpErrorHandlerService } from 'src/app/core/services/error/http-error-handler.service';

/**
 * Kreirano sa: `ng g c components/books`
 */
@Component({
  selector: 'app-books',
  templateUrl: './books.component.html',
  styleUrls: ['./books.component.css']
})
export class BooksComponent implements OnInit {

  books: Book[] = [];

  constructor(
    private bookService: BookService,
    private httpErrorHandlerService: HttpErrorHandlerService) {}

  ngOnInit(): void {
    this.bookService.fetchAllBooks().subscribe({
      next: (books: Book[]) => {
        this.books = books;
        console.log(this.books)
      },
      error: (error: any) => {
        this.httpErrorHandlerService.handle(error);
      }
    })
  }

}
