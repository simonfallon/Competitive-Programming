/// given a set of points, answer queries of nearest point in O(log(n))
bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}

struct Node {
	pt pp;
	ll x0=inf, x1=-inf, y0=inf, y1=-inf;
	Node *first=0, *second=0;

	ll distance(pt p){    ///returns 0 if pt inside bounding box
		ll x = min(max(x0,p.x),x1);
		ll y = min(max(y0,p.y),y1);
		return (pt(x,y)-p).norm2();
	}

	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p : vp){   ///get bounding box
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(sz(vp)>1){   ///splits on median of "bigger" dimension
			sort(all(vp),x1-x0>=y1-y0?onx:ony);
			int m=sz(vp)/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({all(vp)})) {}

	pair<ll,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			if(p==node->pp) return {inf,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		ll bf=f->distance(p), bs=s->distance(p);

		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);          /// bf <= bs

		if(bs<best.fi) best=min(best,search(p,s));
		return best;
	}

	pair<ll,pt> search2(pt p, Node *node, ll dist){
		if(!node->first){
			//avoid query point as answer
			if(p==node->pp) return {inf,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		ll bf=f->distance(p), bs=s->distance(p);

		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best = search2(p,f,dist);

		if(best.fi == dist || bs < best.fi) return search2(p, s, dist);
		return best;
	}

	pair<ll,pt> nearest(pt p){return search(p,root);}			///query for nearest point given a point
	pair<ll,pt> nearest2(pt p, ll dist){return search2(p,root,dist);}	///query for second nearest point given a point and the nearest distance
};
