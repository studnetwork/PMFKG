import { Location } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { AuthorService } from 'src/app/core/services/authors/author.service';
import { HttpErrorHandlerService } from 'src/app/core/services/error/http-error-handler.service';

/**
 * Kreirano sa: `ng g c components/authors/components/new-author`
 */
@Component({
  selector: 'app-new-author',
  templateUrl: './new-author.component.html',
  styleUrls: ['./new-author.component.css']
})
export class NewAuthorComponent implements OnInit {
  name: string = "";
  surname: string = "";
  dateOfBirth: number = -1;

  constructor(
    private authorService: AuthorService,
    private location: Location,
    private httpErrorHandlerService: HttpErrorHandlerService) {}

  ngOnInit(): void {
  }

  createNewAuthor() {
    this.authorService.createAuthor(this.name, this.surname, this.dateOfBirth).subscribe({
      next: () => {
        console.log("Autor je uspesno kreiran");

        this.location.back();
      },
      error: (error: any) => {
        this.httpErrorHandlerService.handle(error);
      }
    });
  }

  back() {

    this.location.back();
  }

}
