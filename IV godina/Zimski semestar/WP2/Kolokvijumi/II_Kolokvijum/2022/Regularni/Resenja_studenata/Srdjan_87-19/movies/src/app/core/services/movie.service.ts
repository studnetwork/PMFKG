import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';
import { Movie } from '../models/movie.model';

@Injectable({
  providedIn: 'root'
})
export class MovieService {

  endpointUrl = `${environment.backendUrl}/movies`;

  constructor(
    private http: HttpClient
  ) { }

  getAll(): Observable<Array<Movie>> {
    return this.http.get<Array<Movie>>(this.endpointUrl);
  }
}
