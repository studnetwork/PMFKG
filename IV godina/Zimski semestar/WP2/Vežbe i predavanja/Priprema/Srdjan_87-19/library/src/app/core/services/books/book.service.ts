import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';
import { Book } from '../../models/book.model';
import { AuthService } from '../auth/auth.service';

/**
 * Kreirano sa: `ng g s core/services/books/book`
 */
@Injectable({
  providedIn: 'root'
})
export class BookService {
  private resourceUrl = `${environment.backendUrl}:${environment.backendPort}/books`;

  constructor(
    private http: HttpClient,
    private authService: AuthService) { }

  fetchAllBooks(): Observable<Book[]> {
    let bearerToken = "Bearer " + this.authService.getToken();
    return this.http.get<Book[]>(this.resourceUrl, { headers: {"Authorization":bearerToken} });
  }

  createNewBook(title: string, author: string, yearOfPublication: number): Observable<void> {
    let bearerToken = "Bearer " + this.authService.getToken();

    let book = {
      title: title,
      author: author,
      yearOfPublication: yearOfPublication
    }

    return this.http.post<void>(this.resourceUrl, book, { headers: {"Authorization":bearerToken} });
  }
}
