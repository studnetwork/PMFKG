import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Author } from 'src/app/core/models/author.model';
import { AuthorService } from 'src/app/core/services/authors/author.service';
import { BookService } from 'src/app/core/services/books/book.service';
import { HttpErrorHandlerService } from 'src/app/core/services/error/http-error-handler.service';
import { Location } from '@angular/common';

/**
 * Kreirano sa: `ng g c components/books/components/new-book`
 */
@Component({
  selector: 'app-new-book',
  templateUrl: './new-book.component.html',
  styleUrls: ['./new-book.component.css']
})
export class NewBookComponent implements OnInit {
  title: string = "";
	yearOfPublication: number = -1;

  chosenAuthor = "";

  authors: Author[] = [];

  constructor(
    private bookService: BookService,
    private authorService: AuthorService,
    private location: Location,
    private httpErrorHandlerService: HttpErrorHandlerService) {}

  ngOnInit(): void {
    // za testiranje
    
    // this.authors: Author[] = [{
    //   _id: "1",
    //   name: "Autor 1",
    //   surname: "Prezime 1",
    //   dateOfBirth: 2001
    // }, {
    //   _id: "2",
    //   name: "Autor 2",
    //   surname: "Prezime 2",
    //   dateOfBirth: 2002
    // }, {
    //   _id: "3",
    //   name: "Autor 3",
    //   surname: "Prezime 3",
    //   dateOfBirth: 2003
    // }, {
    //   _id: "4",
    //   name: "Autor 4",
    //   surname: "Prezime 4",
    //   dateOfBirth: 2004
    // }, {
    //   _id: "5",
    //   name: "Autor 5",
    //   surname: "Prezime 5",
    //   dateOfBirth: 2005
    // }, {
    //   _id: "6",
    //   name: "Autor 6",
    //   surname: "Prezime 6",
    //   dateOfBirth: 2006
    // }];

    this.authorService.fetchAllAuthors().subscribe({
      next: (authors: Author[]) => {
        this.authors = authors;
      },
      error: (error: any) => {
        this.httpErrorHandlerService.handle(error);
      }
    })
  }

  createNewBook(): void {
    this.bookService.createNewBook(this.title, this.chosenAuthor, this.yearOfPublication).subscribe({
      next: () => {
          console.log("Knjiga je kreirana");

          this.location.back();
      },
      error: (error: any) => {
        this.httpErrorHandlerService.handle(error);
      }
    });
  }

  chooseAuthor(authorId: string) {
    this.chosenAuthor = authorId;
  }
}
