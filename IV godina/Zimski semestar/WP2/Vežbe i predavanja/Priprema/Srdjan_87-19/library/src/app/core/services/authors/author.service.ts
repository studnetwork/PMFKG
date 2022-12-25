import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';
import { Author } from '../../models/author.model';
import { AuthService } from '../auth/auth.service';

/**
 * Kreirano sa: `ng g s core/services/authors/author`
 */
@Injectable({
  providedIn: 'root'
})
export class AuthorService {

  private resourceUrl = `${environment.backendUrl}:${environment.backendPort}/author`;

  constructor(
    private http: HttpClient,
    private authService: AuthService) { }

  fetchAllAuthors(): Observable<Author[]> {
    let bearerToken = "Bearer " + this.authService.getToken();
    return this.http.get<Author[]>(this.resourceUrl, { headers: {"Authorization":bearerToken} })
  }

  createAuthor(name: string, surname: string, dateOfBirth: number): Observable<void> {
    let bearerToken = "Bearer " + this.authService.getToken();
    
    let author = { 
      name: name,
      surname: surname,
      dateOfBirth: dateOfBirth
    };

    return this.http.post<void>(this.resourceUrl, author, { headers: {"Authorization":bearerToken} });
  }
}
