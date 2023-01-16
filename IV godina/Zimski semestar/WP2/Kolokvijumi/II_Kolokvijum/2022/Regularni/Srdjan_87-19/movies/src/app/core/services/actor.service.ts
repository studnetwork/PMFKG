import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Actor } from 'src/app/core/models/actor.model'
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class ActorService {

  endpointUrl = `${environment.backendUrl}/actors`;

  constructor(
    private http: HttpClient
  ) { }

  getAllForMovieId(id: string): Observable<Array<Actor>> {
    return this.http.get<Array<Actor>>(this.endpointUrl);
  }
}
